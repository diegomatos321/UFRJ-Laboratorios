--[[
    # Compiladores 2025-01 - Tarefa 3
    Aluno: Diego Vasconcelos Schardosim de Matos
    DRE: 120098723
]]

local inspect = require('inspect')

local keywords = {
    ["and"] = true,
    ["break"] = true,
    ["do"] = true,
    ["else"] = true,
    ["elseif"] = true,
    ["end"] = true,
    ["false"] = true,
    ["for"] = true,
    ["function"] = true,
    ["goto"] = true,
    ["if"] = true,
    ["in"] = true,
    ["local"] = true,
    ["nil"] = true,
    ["not"] = true,
    ["or"] = true,
    ["repeat"] = true,
    ["return"] = true,
    ["then"] = true,
    ["true"] = true,
    ["until"] = true,
    ["while"] = true
}

local function scanner(source)
    local tokens = {}
    local start = 0
    local current = 0
    local line = 1

    local function reportError(row, col, msg)
        io.write(string.format("[%d:%d] Error: %s", row, col, msg))
        os.exit(1)
    end

    local function isAtEnd()
        return current + 1 > string.len(source)
    end

    local function peek(lookAhead)
        if current + lookAhead > string.len(source) == true then
            return '\0'
        else
            return source:sub(current + lookAhead, current + lookAhead)
        end
    end

    local function advance()
        current = current + 1
        local char = source:sub(current, current)
        if char == '\n' then
            line = line + 1
            start = current
        end
        return char
    end

    local function match(expected)
        if isAtEnd() then
            return false
        elseif source:sub(current + 1, current + 1) ~= expected then
            return false
        else
            current = current + 1
            return true
        end
    end

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

    local function identifier()
        local identifierStart = current
        local startCol = current - start
        local startRow = line
        while isAlphaNumeric(peek(1)) and isAtEnd() == false do
            advance()
        end

        local value = source:sub(identifierStart, current)

        if keywords[value] then
            table.insert(tokens, { tag = value, row = startRow, col = startCol, value = '' })
        else
            table.insert(tokens, { tag = 'NOME', row = startRow, col = startCol, value = value })
        end
    end

    local function readNumber()
        local numberStart = current
        local startCol = current - start
        local startRow = line

        if source:sub(current, current) == '0' and (peek(1) == 'x' or peek(1) == 'X') then
            advance()
            while (peek(1) >= 'a' and peek(1) <= 'z') or (peek(1) >= 'A' and peek(1) <= 'Z') do
                advance()
            end
        else
            while isDigit(peek(1)) do
                advance()
            end

            if peek(1) == '.' and isDigit(peek(2)) then
                advance()
                advance()
                while isDigit(peek(1)) do
                    advance()
                end
            end
        end

        local value = source:sub(numberStart, current)
        table.insert(tokens, { tag = 'NUMBER', row = startRow, col = startCol, value = tonumber(value) })
    end

    local function readString()
        local startCol = current - start
        local startRow = line
        local isClosed = false

        local openQuote = source:sub(current, current)
        local buffer = ''
        while isAtEnd() == false do
            if (openQuote == '"' and match('"')) or (openQuote == "'" and match("'")) then
                isClosed = true
                break
            end

            local char = advance()

            if char == "\\" then
                if match('a') then
                    buffer = buffer .. '\a'
                elseif match('b') then
                    buffer = buffer .. '\b'
                elseif match('f') then
                    buffer = buffer .. '\f'
                elseif match('n') then
                    buffer = buffer .. '\n'
                elseif match('r') then
                    buffer = buffer .. '\r'
                elseif match('t') then
                    buffer = buffer .. '\t'
                elseif match('v') then
                    buffer = buffer .. '\v'
                elseif match("\\") then
                    buffer = buffer .. '\\'
                elseif match('"') then
                    buffer = buffer .. '"'
                elseif match("'") then
                    buffer = buffer .. "'"
                elseif match('0') then
                    buffer = buffer .. '\0'
                else
                    reportError(line, current - start, "Invalid escape sequence")
                end
            else
                buffer = buffer .. char
            end
        end

        if isClosed == false then
            reportError(startRow, startCol, 'Unterminated string')
        end

        table.insert(tokens, { tag = 'STRING', row = startRow, col = startCol, value = buffer })
    end

    while isAtEnd() == false do
        local char = advance()

        if char == ' ' or char == '\r' or char == '\t' or char == '\n' then
            -- Ignore whitespace
        elseif char == '+' then
            table.insert(tokens, { tag = '+', row = line, col = current - start, value = '' })
        elseif char == '-' then
            if match('-') then
                if peek(1) == '[' and peek(2) == '[' then
                    while isAtEnd() == false do
                        advance()
                        if peek(1) == ']' and peek(2) == ']' then
                            advance()
                            advance()
                            break
                        end
                    end
                else
                    while peek(1) ~= '\n' and isAtEnd() == false do
                        advance()
                    end
                end
            else
                table.insert(tokens, { tag = '-', row = line, col = current - start, value = '' })
            end
        elseif char == '*' then
            table.insert(tokens, { tag = '*', row = line, col = current - start, value = '' })
        elseif char == '/' then
            if match('/') then
                table.insert(tokens, { tag = '//', row = line, col = current - start, value = '' })
            else
                table.insert(tokens, { tag = '/', row = line, col = current - start, value = '' })
            end
        elseif char == '%' then
            table.insert(tokens, { tag = '%', row = line, col = current - start, value = '' })
        elseif char == '^' then
            table.insert(tokens, { tag = '^', row = line, col = current - start, value = '' })
        elseif char == '#' then
            table.insert(tokens, { tag = '#', row = line, col = current - start, value = '' })
        elseif char == '&' then
            table.insert(tokens, { tag = '&', row = line, col = current - start, value = '' })
        elseif char == '~' then
            if match('=') then
                table.insert(tokens, { tag = '~=', row = line, col = current - start, value = '' })
            else
                table.insert(tokens, { tag = '~', row = line, col = current - start, value = '' })
            end
        elseif char == '|' then
            table.insert(tokens, { tag = '|', row = line, col = current - start, value = '' })
        elseif char == '<' then
            if match('<') then
                table.insert(tokens, { tag = '<<', row = line, col = current - start, value = '' })
            elseif match('=') then
                table.insert(tokens, { tag = '<=', row = line, col = current - start, value = '' })
            else
                table.insert(tokens, { tag = '<', row = line, col = current - start, value = '' })
            end
        elseif char == '>' then
            if match('>') then
                table.insert(tokens, { tag = '>>', row = line, col = current - start, value = '' })
            elseif match('=') then
                table.insert(tokens, { tag = '>=', row = line, col = current - start, value = '' })
            else
                table.insert(tokens, { tag = '>', row = line, col = current - start, value = '' })
            end
        elseif char == '(' then
            table.insert(tokens, { tag = '(', row = line, col = current - start, value = '' })
        elseif char == ')' then
            table.insert(tokens, { tag = ')', row = line, col = current - start, value = '' })
        elseif char == '{' then
            table.insert(tokens, { tag = '{', row = line, col = current - start, value = '' })
        elseif char == '}' then
            table.insert(tokens, { tag = '}', row = line, col = current - start, value = '' })
        elseif char == '[' then
            table.insert(tokens, { tag = '[', row = line, col = current - start, value = '' })
        elseif char == ']' then
            table.insert(tokens, { tag = ']', row = line, col = current - start, value = '' })
        elseif char == ',' then
            table.insert(tokens, { tag = ',', row = line, col = current - start, value = '' })
        elseif char == '.' then
            if match('.') then
                if match('.') then
                    table.insert(tokens, { tag = '...', row = line, col = current - start, value = '' })
                else
                    table.insert(tokens, { tag = '..', row = line, col = current - start, value = '' })
                end
            else
                table.insert(tokens, { tag = '.', row = line, col = current - start, value = '' })
            end
        elseif char == ':' then
            if match(':') then
                table.insert(tokens, { tag = '::', row = line, col = current - start, value = '' })
            else
                table.insert(tokens, { tag = ':', row = line, col = current - start, value = '' })
            end
        elseif char == '!' then
            table.insert(tokens, { tag = '!', row = line, col = current - start, value = '' })
        elseif char == '=' then
            if match('=') then
                table.insert(tokens, { tag = '==', row = line, col = current - start, value = '' })
            else
                table.insert(tokens, { tag = '=', row = line, col = current - start, value = '' })
            end
        elseif char == '"' or char == "'" then
            readString()
        elseif isDigit(char) then
            readNumber()
        elseif isAlpha(char) then
            identifier()
        else
            reportError(line, current - start, 'Unexpected character: ' .. char)
        end
    end

    table.insert(tokens, { tag = 'EOF', row = line, col = current - start, value = '' })

    return tokens
end

local function parser(tokens)
    local current = 1
    local expression = function() end
    local bloco = function() end
    local comando = function() end
    local ifStatement = function() end

    local function reportError(msg)
        local token = tokens[current]

        if token.tag == 'EOF' then
            io.write(string.format("[%d:%d] at end %s", token.row, token.col, msg))
        elseif token.tag == 'NOME' or token.tag == 'NUMBER' then
            io.write(string.format("[%d:%d] at '%s': %s", token.row, token.col, token.value, msg))
        else
            io.write(string.format("[%d:%d] at '%s': %s", token.row, token.col, token.tag, msg))
        end
        os.exit(1)
    end

    local function peek()
        return tokens[current]
    end

    local function previous()
        return tokens[current - 1]
    end

    local function isAtEnd()
        return peek().tag == 'EOF'
    end

    local function advance()
        if isAtEnd() == false then
            current = current + 1
        end
        return previous()
    end

    local function check(type, i)
        if isAtEnd() then
            return false
        end
        return peek().tag == type
    end

    local function consume(type, message)
        if check(type) then
            return advance()
        end

        reportError(message)
    end

    local function match(...)
        local args = { ... }
        for index, type in ipairs(args) do
            if check(type) then
                advance()
                return true
            end
        end

        return false
    end

    local function parseField()
        local field = nil
        if match('STRING') then
            field = { tag = 'ExpString', value = previous().value }
        elseif match('NOME') then
            local key = previous().value

            if match('=') then
                local value = expression()
                return { tag = 'ExpFieldKey', key = key, value = value }
            else
                field = { tag = 'ExpNome', value = key }
            end
        elseif match('NUMBER') then
            field = { tag = 'ExpNumber', value = previous().value }
        else
            reportError('Expected a field name.')
        end

        return { tag = 'ExpFieldKey', key=nil, value = field }
    end

    local function simples()
        if match('true') then
            return { tag = 'ExpBool', value = true }
        elseif match('false') then
            return { tag = 'ExpBool', value = false }
        elseif match('nil') then
            return { tag = 'ExpNil' }
        elseif match('NUMBER') then
            return { tag = 'ExpNumber', value = previous().value }
        elseif match('STRING') then
            return { tag = 'ExpString', value = previous().value }
        elseif match('{') then
            local inits = {}
            if check('}') == false then
                table.insert(inits, parseField())
                while match(',') do
                    if check('}') == false then
                        table.insert(inits, parseField())
                    end
                end
            end
            consume('}', 'Expected "}" after table content.')
            return { tag = 'ExpTable', content = inits }
        else
            reportError('Expected a simple expression.')
        end
    end

    local function primary()
        if match('NOME') then
            return { tag = 'ExpNome', value = previous().value }
        elseif match('(') then
            local expr = expression()
            consume(')', 'Expected ")" after expression.')
            return { tag = 'Expr', exp = expr }
        else
            return simples()
        end
    end

    local function sufixado()
        local expr1 = primary()

        while match('(') do
            local expr2 = expression()
            consume(')', 'Expected ")" after expression.')
            return { tag = 'ExpChamada', expf = expr1, args = expr2 }
        end

        if match('[') then
            local key = expression()
            consume(']', 'Expected "]" after field.')
            consume('=', 'Expected "=" after field.')
            local value = expression()
            return { tag = 'CmdSetTbl', lhs=expr1, key = key, rhs = value }
        end

        if match('.') then
            consume('NOME', 'Expected field name after ".".')
            local key = { tag = 'ExpString', value = previous().value }  -- Apenas para o avaliador me retornarn o valor do campo, e não procurar como variável global
            consume('=', 'Expected "=" after field.')
            local value = expression()

            return { tag = 'CmdSetTbl', lhs=expr1, key = key, rhs = value }
        end

        return expr1
    end

    local function unary()
        if match('-', 'not') then
            local operator = previous()
            local right = unary()
            return { tag = 'ExpUnop', op = operator.tag, exp = right }
        end

        return sufixado()
    end

    local function factor()
        local expr = unary()

        while match('*', '/') do
            local operator = previous()
            local right = unary()
            expr = { tag = 'ExpBinop', op = operator.tag, exp1 = expr, exp2 = right }
        end

        return expr
    end

    local function term()
        local expr = factor()

        while match('+', '-') do
            local operator = previous()
            local right = factor()
            expr = { tag = 'ExpBinop', op = operator.tag, exp1 = expr, exp2 = right }
        end

        return expr
    end

    local function comparison()
        local expr = term()

        while match('>', '>=', '<', '<=', '==', '~=') do
            local operator = previous()
            local right = term()
            expr = { tag = 'ExpBinop', op = operator.tag, exp1 = expr, exp2 = right }
        end

        return expr
    end

    local function andLogical()
        local expr = comparison()

        while match('and') do
            local operator = previous()
            local right = comparison()
            expr = { tag = 'ExpLogical', op = operator.tag, exp1 = expr, exp2 = right }
        end

        return expr
    end

    local function orLogical()
        local expr = andLogical()

        while match('or') do
            local operator = previous()
            local right = andLogical()
            expr = { tag = 'ExpLogical', op = operator.tag, exp1 = expr, exp2 = right }
        end

        return expr
    end

    local function assignment()
        local expr = orLogical()

        if match('=') then
            local equals = previous()
            local value = assignment()

            if expr.tag == 'ExpNome' then
                return { tag = 'CmdSetVar', name = expr, exp = value }
            else
                reportError('Invalid assignment target.')
            end
        end

        return expr
    end

    expression = function()
        return assignment()
    end

    local function whileStatement()
        local condition = expression()

        consume('do', 'Expected "do" after "condition".')

        local commands = {}
        while check('end') == false do
            table.insert(commands, comando())
        end
        consume('end', 'Expected "end" after "while".')

        local body = { tag = 'CmdBloco', comandos = commands }

        return { tag = 'CmdWhile', condition = condition, body = body }
    end

    local function elseStatement()
        if match('end') then
            return nil
        elseif match('else') then
            local commands = {}
            while check('end') == false do
                table.insert(commands, comando())
            end
            consume('end', 'Expected "end" after "else".')
            return { tag = 'CmdBloco', comandos = commands }
        elseif match('elseif') then
            return ifStatement()
        else
            reportError('Expected "else" or "elseif".')
        end
    end

    ifStatement = function()
        local condition = expression()

        consume('then', 'Expected "then" after condition.')

        local commands = {}
        while check('end') == false and check('else') == false and check('elseif') == false do
            table.insert(commands, comando())
        end
        local thenBranch = { tag = 'CmdBloco', comandos = commands }
        local elseBranch = elseStatement()

        return { tag = 'CmdIf', condition = condition, thenBranch = thenBranch, elseBranch = elseBranch }
    end

    comando = function()
        if match('if') then
            return ifStatement()
        elseif match('while') then
            return whileStatement()
        else
            return expression()
        end
    end

    bloco = function()
        local comandos = {}
        while isAtEnd() == false do
            table.insert(comandos, comando())
        end
        return { tag = 'CmdBloco', comandos = comandos }
    end

    return bloco()
end

local function interpreter(bloco)
    local GLOBALS = {}

    local function eval(statement)
        local function reportError(msg)
            io.write(string.format("Error: %s", msg))
            os.exit(1)
        end

        local function checkNumberOperand(operator, right)
            if type(right) == 'number' then
                return true
            end

            reportError('Operand must be a number.')
        end

        local function checkNumberOperands(operator, left, right)
            if type(right) == 'number' and type(left) == 'number' then
                return true
            end

            reportError('Operand must be a number.')
        end

        local function evalExp(expr)
            if expr.tag == "ExpBool" or expr.tag == "ExpNil" or expr.tag == "ExpNumber" or expr.tag == "ExpString" then
                return expr.value
            elseif expr.tag == "ExpNome" then
                if expr.value == 'pi' then
                    return math.pi
                else
                    return GLOBALS[expr.value]
                end
            elseif expr.tag == "Expr" then
                return evalExp(expr.exp)
            elseif expr.tag == "ExpUnop" then
                local right = evalExp(expr.exp)
                if expr.op == '-' then
                    checkNumberOperand(expr.tag, right)
                    return -right
                elseif expr.op == 'not' then
                    return not right -- o mesmo de lua
                else
                    return nil
                end
            elseif expr.tag == "ExpBinop" then
                local left = evalExp(expr.exp1)
                local right = evalExp(expr.exp2)

                if expr.op == '+' then
                    checkNumberOperands(expr.op, left, right)
                    return left + right
                elseif expr.op == '-' then
                    checkNumberOperands(expr.op, left, right)
                    return left - right
                elseif expr.op == '*' then
                    checkNumberOperands(expr.op, left, right)
                    return left * right
                elseif expr.op == '/' then
                    checkNumberOperands(expr.op, left, right)
                    return left / right
                elseif expr.op == '^' then
                    checkNumberOperands(expr.op, left, right)
                    return left ^ right
                elseif expr.op == '==' then
                    return left == right
                elseif expr.op == '~=' then
                    return left ~= right
                elseif expr.op == '<' then
                    checkNumberOperands(expr.op, left, right)
                    return left < right
                elseif expr.op == '<=' then
                    checkNumberOperands(expr.op, left, right)
                    return left <= right
                elseif expr.op == '>' then
                    checkNumberOperands(expr.op, left, right)
                    return left > right
                elseif expr.op == '>=' then
                    checkNumberOperands(expr.op, left, right)
                    return left >= right
                elseif expr.op == '..' then
                    return left .. right
                else
                    return nil
                end
            elseif expr.tag == "ExpLogical" then
                local left = evalExp(expr.exp1)

                if expr.op == 'or' then
                    if left then
                        return left
                    end
                else
                    if not left then
                        return left
                    end
                end

                return evalExp(expr.exp2)
            elseif expr.tag == "ExpChamada" then
                local right = evalExp(expr.args)

                if expr.expf.value == 'print' then
                    print(right)
                    return nil
                elseif type(right) == 'number' then
                    return math[expr.expf.value](right)
                else
                    -- io.write('Error: ' .. expr.expf.value .. ' is not a function.\n')
                    reportError('Operand must be a number.')
                end
            elseif expr.tag == "ExpTable" then
                local content = {}
                for _, field in ipairs(expr.content) do
                    if field.tag == 'ExpFieldKey' then
                        local value = evalExp(field.value)
                        if field.key == nil then
                            table.insert(content, value)
                        else
                            content[field.key] = value
                        end
                    else
                        reportError('Expected a field name.')
                    end
                end

                return content
            else
                reportError('Undefined expression.')
            end
        end

        local function evalCmd(statement)
            if statement.tag == 'CmdBloco' then
                for _, cmd in ipairs(statement.comandos) do
                    evalCmd(cmd)
                end
            elseif statement.tag == 'CmdIf' then
                local condition = evalExp(statement.condition)
                if condition then
                    evalCmd(statement.thenBranch)
                else
                    if statement.elseBranch then
                        evalCmd(statement.elseBranch)
                    end
                end
            elseif statement.tag == 'CmdWhile' then
                while evalExp(statement.condition) do
                    evalCmd(statement.body)
                end
            elseif statement.tag == "CmdSetVar" then
                local name = statement.name.value
                local value = evalExp(statement.exp)
            
                if statement.name.tag == 'ExpNome' then
                    GLOBALS[name] = value
                else
                    reportError('Expected variable name.')
                end
            elseif statement.tag == 'CmdSetTbl' then
                local lhs = evalExp(statement.lhs)
                local key = evalExp(statement.key)
                local value = evalExp(statement.rhs)
                
                if statement.lhs.tag == 'ExpNome' then
                    lhs[key] = value
                else
                    reportError('Expected variable name.')
                end
            elseif statement.tag == 'ExpChamada' then
                evalExp(statement)
            else
                reportError('Undefined command.')
            end
        end

        return evalCmd(bloco)
    end

    return eval(bloco)
end

local function main()
    local source = io.read('*a')
    local tokens = scanner(source)

    io.write('Tokens\n')
    io.write('Row\tCol\tTokens\tValor\n')
    for _, token in ipairs(tokens) do
        if token.tag == 'EOF' then
            io.write(token.row .. '\t' .. token.col .. '\t' .. 'EOF\n')
        else
            io.write(token.row .. '\t' .. token.col .. '\t' .. token.tag .. '\t' .. token.value .. '\n')
        end
    end

    local statements = parser(tokens)

    io.write('\nArvore de Sintaxe\n')
    io.write(inspect(statements))
    io.write('\n')

    interpreter(statements)
end

main()
