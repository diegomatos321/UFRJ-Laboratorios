--[[
    # Compiladores 2025-01 - Tarefa 5
    Aluno: Diego Vasconcelos Schardosim de Matos
    DRE: 120098723
]]

local inspect = require('inspect')

local function assembler(bytecodePath)
    local closures = {}
    local currentClosureIdx = 1
    local labels = {}

    local function isDigit(char)
        local code = string.byte(char)

        return code >= string.byte(0) and code <= string.byte(9)
    end

    local function isAlpha(char)
        local code = string.byte(char)
        return (code >= string.byte('a') and code <= string.byte('z')) or
            (code >= string.byte('A') and code <= string.byte('Z')) or
            code == string.byte('_')
    end

    local function isAlphaNumeric(char)
        return isAlpha(char) or isDigit(char)
    end

    local function isWhitespace(char)
        return char == ' ' or char == '\t' or char == '\n' or char == '\r'
    end

    local function firstPass()
        for line in io.lines(bytecodePath) do
            local command = {}

            local current = 0
            while current + 1 <= #line do
                current = current + 1
                local char = line:sub(current, current)

                if isWhitespace(char) then
                    -- Skip whitespace
                elseif char == '#' then
                    -- Skip comment
                    while current + 1 <= #line do
                        current = current + 1
                    end
                elseif char == '"' then
                    local isClosed = false
                    local buffer = ''
                    while current + 1 <= #line do
                        current = current + 1
                        local char = line:sub(current, current)
                        if char == '\\' then
                            current = current + 1
                            local nextChar = line:sub(current, current)
                            if nextChar == 'a' then
                                buffer = buffer .. '\a'
                            elseif nextChar == 'b' then
                                buffer = buffer .. '\b'
                            elseif nextChar == 'f' then
                                buffer = buffer .. '\f'
                            elseif nextChar == 'n' then
                                buffer = buffer .. '\n'
                            elseif nextChar == 'r' then
                                buffer = buffer .. '\r'
                            elseif nextChar == 't' then
                                buffer = buffer .. '\t'
                            elseif nextChar == 'v' then
                                buffer = buffer .. '\v'
                            elseif nextChar == '"' then
                                buffer = buffer .. '"'
                            elseif nextChar == '\\' then
                                buffer = buffer .. '\\'
                            elseif nextChar == '0' then
                                buffer = buffer .. '\0'
                            else
                                io.write("Error: Invalid escape sequence '\\" .. nextChar .. "'.\n")
                                os.exit(1)
                            end
                        elseif char == '"' then
                            isClosed = true
                            break
                        else
                            buffer = buffer .. char
                        end
                    end

                    if isClosed then
                        command[#command + 1] = { tag = 'STRING', value = buffer }
                    else
                        io.write("Error: Unclosed string literal.\n")
                        os.exit(1)
                    end
                elseif isDigit(char) then
                    local start = current
                    while current + 1 <= #line do
                        local nextChar = line:sub(current + 1, current + 1)
                        if nextChar == '.' or isDigit(nextChar) then
                            current = current + 1
                        else
                            break
                        end
                    end

                    local value = line:sub(start, current)
                    command[#command + 1] = { tag = 'NUMBER', value = tonumber(value) }
                elseif isAlpha(char) then
                    local start = current
                    while current + 1 <= #line and isAlphaNumeric(line:sub(current + 1, current + 1)) do
                        current = current + 1
                    end

                    -- Ended with label
                    if line:sub(current + 1, current + 1) == ':' then
                        local labelName = line:sub(start, current)
                        local currentClosure = closures[currentClosureIdx]
                        labels[labelName] = #currentClosure + 1
                        current = current + 1
                    else
                        command[#command + 1] = line:sub(start, current)
                    end
                else
                    io.write("Error: Invalid character '" .. char .. "' in bytecode.\n")
                    os.exit(1)
                end
            end

            if #command > 0 then
                if command[1] == 'CLOSURE' then
                    local idx = command[2]
                    if idx.tag ~= 'NUMBER' then
                        io.write("Error: CLOSURE expects a number index.\n")
                        os.exit(1)
                    end

                    -- Create a new closure
                    closures[idx.value + 1] = {}
                    currentClosureIdx = idx.value + 1
                else
                    local currentClosure = closures[currentClosureIdx]
                    if not currentClosure then
                        io.write("Error: CLOSURE expected before other instructions.\n")
                        os.exit(1)
                    end

                    currentClosure[#currentClosure + 1] = command
                end
            end
        end
    end

    local function secondPass()
        for i = 1, #closures do
            local closure = closures[i]

            for i = 1, #closure do
                local instruction = closure[i]
                local op = instruction[1]

                if op == 'JUMP' or op == 'JUMP_TRUE' or op == 'JUMP_FALSE' then
                    local target = instruction[2]
                    if labels[target] then
                        closure[i] = { op, labels[target] }
                    else
                        io.write("Error: Label '" .. target .. "' not found.\n")
                        os.exit(1)
                    end
                end
            end
        end
    end

    firstPass()
    secondPass()

    return closures
end

local function run_vm(program)
    local closures = {}

    for i = 1, #program do
        local closure = program[i]
        closures[#closures + 1] = {
            tag = 'ValLuaFunc',
            program = closure,
        }
    end
    local callStack = {
        { pc = 1, stack = {}, program = closures[1].program, locals = {} }
    }

    local function reportError(msg)
        local currentFrame = callStack[#callStack]
        local pc = currentFrame.pc

        -- show line on error
        io.write("Error at instruction " .. pc .. ": " .. msg .. '\n')
        os.exit(1)
    end

    local function ValString(value)
        return { tag = 'ValString', value = value }
    end

    local function ValNumber(value)
        return { tag = 'ValNumber', value = value }
    end

    local function ValBoolean(value)
        return { tag = 'ValBoolean', value = value }
    end

    local function ValNil()
        return { tag = 'ValNil' }
    end

    local function ValTable()
        return { tag = 'ValTable', content = {} }
    end

    local globals = {
        print = {
            tag = 'ValLibFunc',
            arity = 1,
            call = function(args)
                local arg = args[1]
                -- io.write(inspect(arg) .. '\n')
                if arg.tag == 'ValString' then
                    io.write(arg.value .. '\n')
                elseif arg.tag == 'ValNumber' then
                    io.write(tostring(arg.value) .. '\n')
                elseif arg.tag == 'ValBool' then
                    io.write(tostring(arg.value) .. '\n')
                elseif arg.tag == 'ValNil' then
                    io.write('nil\n')
                else
                    reportError('print expects a string, number, boolean, or nil.')
                end

                return ValNil()
            end
        },
        math = {
            tag = 'ValTable',
            content = {
                sqrt = {
                    tag = 'ValLibFunc',
                    arity = 1,
                    call = function(args)
                        local arg = args[1]
                        if arg.tag ~= 'ValNumber' then
                            reportError('math.sqrt expects a number.')
                        end
                        return ValNumber(math.sqrt(arg.value))
                    end
                },
            }
        }
    }

    local function isTruthy(value)
        if value.tag == 'ValNil' then
            return false
        elseif value.tag == 'ValBool' then
            return value.value
        else
            return true
        end
    end

    local function isEqual(a, b)
        if a.tag == 'ValNil' and b.tag == 'ValNil' then
            return true
        elseif a.tag == 'ValNil' then
            return false
        else
            return a.value == b.value
        end
    end

    local function checkTypeAndOperand(type, ...)
        local args = { ... }
        if #args == 0 then
            reportError('No arguments provided for operand check.')
        end

        for i = 1, #args do
            local operand = args[i]
            if type == 'Number' and operand.tag ~= 'ValNumber' then
                reportError('Operand must be a number.')
            elseif type == 'String' and operand.tag ~= 'ValString' then
                reportError('Operand must be a string.')
            elseif type == 'Bool' and operand.tag ~= 'ValBool' then
                reportError('Operand must be a boolean.')
            elseif type == 'Table' and operand.tag ~= 'ValTable' then
                reportError('Operand must be a table.')
            elseif type == 'Nil' and operand.tag ~= 'ValNil' then
                reportError('Operand must be nil.')
            end
        end
    end

    local currentFrame = callStack[#callStack]

    while currentFrame.pc <= #currentFrame.program do
        local currentFrame = callStack[#callStack]

        local instruction = currentFrame.program[currentFrame.pc]
        currentFrame.pc = currentFrame.pc + 1

        local op = instruction[1]
        -- io.write(currentFrame.pc .. ": " .. op .. "\n")

        if op == 'PUSH_NUMBER' then
            local data = instruction[2]

            if data.tag == 'NUMBER' then
                currentFrame.stack[#currentFrame.stack + 1] = ValNumber(data.value)
            else
                reportError("Expected a number value.")
            end
        elseif op == 'PUSH_STRING' then
            local data = instruction[2]

            if data.tag == 'STRING' then
                currentFrame.stack[#currentFrame.stack + 1] = ValString(data.value)
            else
                reportError("Expected a string value.")
            end
        elseif op == 'PUSH_TRUE' then
            currentFrame.stack[#currentFrame.stack + 1] = ValBoolean(true)
        elseif op == 'PUSH_FALSE' then
            currentFrame.stack[#currentFrame.stack + 1] = ValBoolean(false)
        elseif op == 'PUSH_NIL' then
            currentFrame.stack[#currentFrame.stack + 1] = ValNil()
        elseif op == 'PUSH_CLOSURE' then
            local idx = instruction[2]

            if idx.tag ~= 'NUMBER' then
                reportError("Expected a number value.")
            end

            if closures[idx.value + 1] then
                currentFrame.stack[#currentFrame.stack + 1] = closures[idx.value + 1]
            else
                reportError("Undefined user Function index")
            end
        elseif op == 'POP' then
            table.remove(currentFrame.stack)
        elseif op == 'SET_GLOBAL' then
            local name = instruction[2]
            globals[name] = table.remove(currentFrame.stack)
        elseif op == 'GET_GLOBAL' then
            local name = instruction[2]
            if globals[name] ~= nil then
                currentFrame.stack[#currentFrame.stack + 1] = globals[name]
            else
                currentFrame.stack[#currentFrame.stack + 1] = ValNil()
            end
        elseif op == 'SET_LOCAL' then
            local idx = instruction[2]
            if idx.tag ~= 'NUMBER' then
                reportError("SET_LOCAL expects a number index.")
            end

            currentFrame.locals[idx.value] = table.remove(currentFrame.stack)
        elseif op == 'GET_LOCAL' then
            local idx = instruction[2]
            if idx.tag ~= 'NUMBER' then
                reportError("GET_LOCAL expects a number index.")
            end

            if currentFrame.locals[idx.value] then
                currentFrame.stack[#currentFrame.stack + 1] = currentFrame.locals[idx.value]
            else
                reportError("Local variable at index " .. idx.value .. " not found.")
            end
        elseif op == 'NEG' then
            local data = table.remove(currentFrame.stack)
            checkTypeAndOperand('Number', data)
            currentFrame.stack[#currentFrame.stack + 1] = ValNumber(-data.value)
        elseif op == 'NOT' then
            local data = table.remove(currentFrame.stack)
            currentFrame.stack[#currentFrame.stack + 1] = ValBoolean(not isTruthy(data))
        elseif op == 'ADD' then
            local b = table.remove(currentFrame.stack)
            local a = table.remove(currentFrame.stack)

            checkTypeAndOperand('Number', a, b)
            currentFrame.stack[#currentFrame.stack + 1] = ValNumber(a.value + b.value)
        elseif op == 'SUB' then
            local b = table.remove(currentFrame.stack)
            local a = table.remove(currentFrame.stack)

            checkTypeAndOperand('Number', a, b)
            currentFrame.stack[#currentFrame.stack + 1] = ValNumber(a.value - b.value)
        elseif op == 'MUL' then
            local b = table.remove(currentFrame.stack)
            local a = table.remove(currentFrame.stack)

            checkTypeAndOperand('Number', a, b)
            currentFrame.stack[#currentFrame.stack + 1] = ValNumber(a.value * b.value)
        elseif op == 'DIV' then
            local b = table.remove(currentFrame.stack)
            local a = table.remove(currentFrame.stack)

            checkTypeAndOperand('Number', a, b)
            if b.value == 0 then
                reportError("Division by zero.")
            end
            currentFrame.stack[#currentFrame.stack + 1] = ValNumber(a.value / b.value)
        elseif op == 'POW' then
            local b = table.remove(currentFrame.stack)
            local a = table.remove(currentFrame.stack)

            checkTypeAndOperand('Number', a, b)
            currentFrame.stack[#currentFrame.stack + 1] = ValNumber(a.value ^ b.value)
        elseif op == 'EQ' then
            local b = table.remove(currentFrame.stack)
            local a = table.remove(currentFrame.stack)

            currentFrame.stack[#currentFrame.stack + 1] = ValBoolean(isEqual(a, b))
        elseif op == 'NEQ' then
            local b = table.remove(currentFrame.stack)
            local a = table.remove(currentFrame.stack)
            currentFrame.stack[#currentFrame.stack + 1] = ValBoolean(not isEqual(a, b))
        elseif op == 'LT' then
            local b = table.remove(currentFrame.stack)
            local a = table.remove(currentFrame.stack)

            checkTypeAndOperand('Number', a, b)
            currentFrame.stack[#currentFrame.stack + 1] = ValBoolean(a.value < b.value)
        elseif op == 'LEQ' then
            local b = table.remove(currentFrame.stack)
            local a = table.remove(currentFrame.stack)

            checkTypeAndOperand('Number', a, b)
            currentFrame.stack[#currentFrame.stack + 1] = ValBoolean(a.value <= b.value)
        elseif op == 'GT' then
            local b = table.remove(currentFrame.stack)
            local a = table.remove(currentFrame.stack)

            checkTypeAndOperand('Number', a, b)
            currentFrame.stack[#currentFrame.stack + 1] = ValBoolean(a.value > b.value)
        elseif op == 'GEQ' then
            local b = table.remove(currentFrame.stack)
            local a = table.remove(currentFrame.stack)

            checkTypeAndOperand('Number', a, b)
            currentFrame.stack[#currentFrame.stack + 1] = ValBoolean(a.value >= b.value)
        elseif op == 'CONCAT' then
            local b = table.remove(currentFrame.stack)
            local a = table.remove(currentFrame.stack)

            checkTypeAndOperand('String', a, b)
            currentFrame.stack[#currentFrame.stack + 1] = ValString(a.value .. b.value)
        elseif op == 'LEN' then
            local data = table.remove(currentFrame.stack)
            if data.tag == 'ValString' then
                currentFrame.stack[#currentFrame.stack + 1] = ValNumber(#data.value)
            elseif data.tag == 'ValTable' then
                currentFrame.stack[#currentFrame.stack + 1] = ValNumber(#data.content)
            else
                reportError("LEN expects a string or table.")
            end
        elseif op == 'NEW_TABLE' then
            currentFrame.stack[#currentFrame.stack + 1] = ValTable()
        elseif op == 'SET_TABLE' then
            local value = table.remove(currentFrame.stack)
            local key = table.remove(currentFrame.stack)
            local tbl = table.remove(currentFrame.stack)

            if key.tag ~= 'ValString' and key.tag ~= 'ValNumber' then
                reportError("SET_TABLE expects a string or number key.")
            end

            if tbl.tag == 'ValTable' then
                tbl.content[key.value] = value
                currentFrame.stack[#currentFrame.stack + 1] = tbl
            else
                io.write("Attempted to set table field on non-table value.")
                os.exit(1)
            end
        elseif op == 'GET_TABLE' then
            local key = table.remove(currentFrame.stack)
            local tbl = table.remove(currentFrame.stack)

            if key.tag ~= 'ValString' and key.tag ~= 'ValNumber' then
                reportError("GET_TABLE expects a string or number key.")
            end

            if tbl.tag == 'ValTable' then
                if tbl.content[key.value] == nil then
                    currentFrame.stack[#currentFrame.stack + 1] = ValNil()
                else
                    currentFrame.stack[#currentFrame.stack + 1] = tbl.content[key.value]
                end
            else
                io.write("Attempted to get table field from non-table value.")
                os.exit(1)
            end
        elseif op == 'JUMP' then
            local target = instruction[2]
            currentFrame.pc = target
        elseif op == 'JUMP_TRUE' then
            local target = instruction[2]
            local condition = table.remove(currentFrame.stack)
            if condition.value then
                currentFrame.pc = target
            end
        elseif op == 'JUMP_FALSE' then
            local target = instruction[2]
            local condition = table.remove(currentFrame.stack)
            -- io.write(inspect(condition) .. '\n')
            if not condition.value then
                currentFrame.pc = target
            end
        elseif op == 'CALL' then
            local nargs = instruction[2]
            local args = {}
            for i = nargs.value, 1, -1 do
                if #currentFrame.stack == 0 then
                    io.write("Stack underflow during CALL.")
                    os.exit(1)
                end
                args[i] = table.remove(currentFrame.stack)
            end
            local func = table.remove(currentFrame.stack)

            if func.tag == 'ValLibFunc' then
                if #args ~= func.arity then
                    io.write("Function '" .. func.name .. "' expects " ..
                        func.arity .. " arguments, got " .. #args .. ".")
                    os.exit(1)
                end
                local returnValue = func.call(args)
                currentFrame.stack[#currentFrame.stack + 1] = returnValue
            elseif func.tag == 'ValLuaFunc' then
                local newFrame = {
                    pc = 1,
                    stack = {},
                    program = func.program,
                    locals = {}
                }

                for i = 1, #args do
                    newFrame.locals[#newFrame.locals + 1] = args[i]
                end

                callStack[#callStack + 1] = newFrame
                currentFrame = callStack[#callStack]
            else
                io.write("Attempted to call a non-function value.")
                os.exit(1)
            end
        elseif op == 'RETURN' then
            local closureResult = table.remove(currentFrame.stack)

            local nextFrame = callStack[#callStack - 1]
            nextFrame.stack[#nextFrame.stack + 1] = closureResult

            table.remove(callStack)
            currentFrame = callStack[#callStack]
        elseif op == 'EXIT' then
            os.exit(0)
        else
            io.write("Unknown instruction '" .. op .. "'.")
            os.exit(1)
        end
    end
end

local function main()
    if #arg ~= 1 then
        io.write("Usage: lua vm.lua <bytecode_path>")
        os.exit(1)
    end

    local bytecodePath = arg[1]
    local program = assembler(bytecodePath)

    run_vm(program)
end

main()
