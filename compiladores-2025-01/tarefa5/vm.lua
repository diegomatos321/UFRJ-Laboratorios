--[[
    # Compiladores 2025-01 - Tarefa 5
    Aluno: Diego Vasconcelos Schardosim de Matos
    DRE: 120098723
]]

local inspect = require('inspect')

local function load_bytecode(bytecodePath)
    local program = {}
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

    for line in io.lines(bytecodePath) do
        local command = {}

        local current = 0
        while current + 1 <= #line do
            current = current + 1
            local char = line:sub(current, current)

            if isWhitespace(char) then
                -- Skip whitespace
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
                while current + 1 <= #line and isDigit(line:sub(current + 1, current + 1)) do
                    current = current + 1
                end
                command[#command + 1] = { tag = 'NUMBER', value = tonumber(line:sub(start, current)) }
            elseif isAlpha(char) then
                local start = current
                while current + 1 <= #line and isAlphaNumeric(line:sub(current + 1, current + 1)) do
                    current = current + 1
                end

                -- Ended with label
                if line:sub(current + 1, current + 1) == ':' then
                    local labelName = line:sub(start, current)
                    current = current + 1
                    labels[labelName] = #program
                else
                    command[#command + 1] = line:sub(start, current)
                end
            else
                io.write("Error: Invalid character '" .. char .. "' in bytecode.\n")
                os.exit(1)
            end
        end

        if #command > 0 then
            program[#program + 1] = command
        end
    end

    return program, labels
end

local function run_vm(program, labels)
    local pc = 0
    local stack = {}

    local function reportError(msg)
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

    while pc < #program do
        local instruction = program[pc + 1]
        pc = pc + 1

        local op = instruction[1]
        -- io.write(inspect(instruction) .. '\n')

        if op == 'PUSH_NUMBER' then
            local data = instruction[2]
            
            if data.tag == 'NUMBER' then
                stack[#stack + 1] = ValNumber(data.value)
            else
                reportError("Error: Expected a number value.")
            end
        elseif op == 'PUSH_STRING' then
            local data = instruction[2]
            
            if data.tag == 'STRING' then
                stack[#stack + 1] = ValString(data.value)
            else
                reportError("Error: Expected a string value.")
            end
        elseif op == 'PUSH_TRUE' then
            stack[#stack + 1] = ValBoolean(true)
        elseif op == 'PUSH_FALSE' then
            stack[#stack + 1] = ValBoolean(false)
        elseif op == 'PUSH_NIL' then
            stack[#stack + 1] = ValNil()
        elseif op == 'POP' then

        elseif op == 'SET_GLOBAL' then
            local name = instruction[2]
            globals[name] = stack[#stack]
            table.remove(stack, #stack)
        elseif op == 'GET_GLOBAL' then
            local name = instruction[2]
            if globals[name] ~= nil then
                stack[#stack + 1] = globals[name]
            else
                reportError("Error: Global variable '" .. name .. "' not found.")
            end
        elseif op == 'NEG' then
            local data = table.remove(stack, #stack)
            checkTypeAndOperand('Number', data)
            stack[#stack + 1] = ValNumber(-data.value)
        elseif op == 'NOT' then
            local data = table.remove(stack, #stack)
            stack[#stack + 1] = ValBoolean(not isTruthy(data))
        elseif op == 'ADD' then
            local b = table.remove(stack, #stack)
            local a = table.remove(stack, #stack)

            checkTypeAndOperand('Number', a, b)
            stack[#stack + 1] = ValNumber(a.value + b.value)
        elseif op == 'SUB' then
            local b = table.remove(stack, #stack)
            local a = table.remove(stack, #stack)

            checkTypeAndOperand('Number', a, b)
            stack[#stack + 1] = ValNumber(a.value - b.value)
        elseif op == 'MUL' then
            local b = table.remove(stack, #stack)
            local a = table.remove(stack, #stack)

            checkTypeAndOperand('Number', a, b)
            stack[#stack + 1] = ValNumber(a.value * b.value)
        elseif op == 'DIV' then
            local b = table.remove(stack, #stack)
            local a = table.remove(stack, #stack)

            checkTypeAndOperand('Number', a, b)
            if b.value == 0 then
                reportError("Error: Division by zero.")
            end
            stack[#stack + 1] = ValNumber(a.value / b.value)
        elseif op == 'POW' then
            local b = table.remove(stack, #stack)
            local a = table.remove(stack, #stack)

            checkTypeAndOperand('Number', a, b)
            stack[#stack + 1] = ValNumber(a.value ^ b.value)
        elseif op == 'EQ' then
            local b = table.remove(stack, #stack)
            local a = table.remove(stack, #stack)

            stack[#stack + 1] = ValBoolean(isEqual(a, b))
        elseif op == 'NEQ' then
            local b = table.remove(stack, #stack)
            local a = table.remove(stack, #stack)
            stack[#stack + 1] = ValBoolean(not isEqual(a, b))
        elseif op == 'LT' then
            local b = table.remove(stack, #stack)
            local a = table.remove(stack, #stack)

            checkTypeAndOperand('Number', a, b)
            stack[#stack + 1] = ValBoolean(a.value < b.value)
        elseif op == 'LEQ' then
            local b = table.remove(stack, #stack)
            local a = table.remove(stack, #stack)

            checkTypeAndOperand('Number', a, b)
            stack[#stack + 1] = ValBoolean(a.value <= b.value)
        elseif op == 'GT' then
            local b = table.remove(stack, #stack)
            local a = table.remove(stack, #stack)

            checkTypeAndOperand('Number', a, b)
            stack[#stack + 1] = ValBoolean(a.value > b.value)
        elseif op == 'GEQ' then
            local b = table.remove(stack, #stack)
            local a = table.remove(stack, #stack)

            checkTypeAndOperand('Number', a, b)
            stack[#stack + 1] = ValBoolean(a.value >= b.value)
        elseif op == 'CONCAT' then
            local b = table.remove(stack, #stack)
            local a = table.remove(stack, #stack)

            checkTypeAndOperand('String', a, b)
            stack[#stack + 1] = ValString(a.value .. b.value)
        elseif op == 'NEW_TABLE' then
            stack[#stack + 1] = ValTable()
        elseif op == 'SET_TABLE' then
            local value = table.remove(stack, #stack)
            local key = table.remove(stack, #stack)
            local tbl = table.remove(stack, #stack)
            if tbl.tag == 'ValTable' then
                tbl.content[key] = value
                stack[#stack + 1] = tbl
            else
                io.write("Error: Attempted to set table field on non-table value.")
                os.exit(1)
            end
        elseif op == 'GET_TABLE' then
            local key = table.remove(stack, #stack)
            local tbl = table.remove(stack, #stack)
            if tbl.tag == 'ValTable' then
                stack[#stack + 1] = tbl.content[key]
            else
                io.write("Error: Attempted to get table field from non-table value.")
                os.exit(1)
            end
        elseif op == 'JUMP' then
            local target = instruction[2]
            if labels[target] then
                pc = labels[target]
            else
                io.write("Error: Label '" .. target .. "' not found.")
                os.exit(1)
            end
        elseif op == 'JUMP_TRUE' then
            local target = instruction[2]
            if labels[target] then
                local condition = table.remove(stack, #stack)
                if condition.value then
                    pc = labels[target]
                end
            else
                io.write("Error: Label '" .. target .. "' not found.")
                os.exit(1)
            end
        elseif op == 'JUMP_FALSE' then
            local target = instruction[2]
            if labels[target] then
                local condition = table.remove(stack, #stack)
                if not condition then
                    pc = labels[target]
                end
            else
                io.write("Error: Label '" .. target .. "' not found.")
                os.exit(1)
            end
        elseif op == 'CALL' then
            local nargs = instruction[2]
            local args = {}
            for i = 1, nargs.value do
                if #stack == 0 then
                    io.write("Error: Stack underflow during CALL.")
                    os.exit(1)
                end
                args[#args + 1] = table.remove(stack, #stack)
            end
            local func = table.remove(stack, #stack)

            if func.tag == 'ValLibFunc' then
                if #args ~= func.arity then
                    io.write("Error: Function '" ..
                        func.name .. "' expects " .. func.arity .. " arguments, got " .. #args .. ".")
                    os.exit(1)
                end
                func.call(args)
            else
                io.write("Error: Attempted to call a non-function value.")
                os.exit(1)
            end
        elseif op == 'EXIT' then

        else
            io.write("Error: Unknown instruction '" .. op .. "'.")
            os.exit(1)
        end
    end
end

local function main()
    if #arg < 1 then
        io.write("Usage: lua vm.lua <bytecode_path>")
        os.exit(1)
    end

    local bytecodePath = arg[1]
    local program, labels = load_bytecode(bytecodePath)

    -- io.write(inspect(program) .. '\n')
    -- io.write(inspect(labels) .. '\n')

    run_vm(program, labels)
end

main()
