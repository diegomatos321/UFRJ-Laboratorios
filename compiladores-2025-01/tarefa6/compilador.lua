--[[
    # Compiladores 2025-01 - Tarefa 5
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

local function lexer(source)
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
            tokens[#tokens + 1] = { tag = value, row = startRow, col = startCol, value = '' }
        else
            tokens[#tokens + 1] = { tag = 'NOME', row = startRow, col = startCol, value = value }
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
        tokens[#tokens + 1] = { tag = 'NUMBER', row = startRow, col = startCol, value = tonumber(value) }
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

        tokens[#tokens + 1] = { tag = 'STRING', row = startRow, col = startCol, value = buffer }
    end

    while isAtEnd() == false do
        local char = advance()

        if char == ' ' or char == '\r' or char == '\t' or char == '\n' then
            -- Ignore whitespace
        elseif char == '+' then
            tokens[#tokens + 1] = { tag = '+', row = line, col = current - start, value = '' }
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
                tokens[#tokens + 1] = { tag = '-', row = line, col = current - start, value = '' }
            end
        elseif char == '*' then
            tokens[#tokens + 1] = { tag = '*', row = line, col = current - start, value = '' }
        elseif char == '/' then
            if match('/') then
                tokens[#tokens + 1] = { tag = '//', row = line, col = current - start, value = '' }
            else
                tokens[#tokens + 1] = { tag = '/', row = line, col = current - start, value = '' }
            end
        elseif char == '%' then
            tokens[#tokens + 1] = { tag = '%', row = line, col = current - start, value = '' }
        elseif char == '^' then
            tokens[#tokens + 1] = { tag = '^', row = line, col = current - start, value = '' }
        elseif char == '#' then
            tokens[#tokens + 1] = { tag = '#', row = line, col = current - start, value = '' }
        elseif char == '&' then
            tokens[#tokens + 1] = { tag = '&', row = line, col = current - start, value = '' }
        elseif char == '~' then
            if match('=') then
                tokens[#tokens + 1] = { tag = '~=', row = line, col = current - start, value = '' }
            else
                tokens[#tokens + 1] = { tag = '~', row = line, col = current - start, value = '' }
            end
        elseif char == '|' then
            tokens[#tokens + 1] = { tag = '|', row = line, col = current - start, value = '' }
        elseif char == '<' then
            if match('<') then
                tokens[#tokens + 1] = { tag = '<<', row = line, col = current - start, value = '' }
            elseif match('=') then
                tokens[#tokens + 1] = { tag = '<=', row = line, col = current - start, value = '' }
            else
                tokens[#tokens + 1] = { tag = '<', row = line, col = current - start, value = '' }
            end
        elseif char == '>' then
            if match('>') then
                tokens[#tokens + 1] = { tag = '>>', row = line, col = current - start, value = '' }
            elseif match('=') then
                tokens[#tokens + 1] = { tag = '>=', row = line, col = current - start, value = '' }
            else
                tokens[#tokens + 1] = { tag = '>', row = line, col = current - start, value = '' }
            end
        elseif char == '(' then
            tokens[#tokens + 1] = { tag = '(', row = line, col = current - start, value = '' }
        elseif char == ')' then
            tokens[#tokens + 1] = { tag = ')', row = line, col = current - start, value = '' }
        elseif char == '{' then
            tokens[#tokens + 1] = { tag = '{', row = line, col = current - start, value = '' }
        elseif char == '}' then
            tokens[#tokens + 1] = { tag = '}', row = line, col = current - start, value = '' }
        elseif char == '[' then
            tokens[#tokens + 1] = { tag = '[', row = line, col = current - start, value = '' }
        elseif char == ']' then
            tokens[#tokens + 1] = { tag = ']', row = line, col = current - start, value = '' }
        elseif char == ',' then
            tokens[#tokens + 1] = { tag = ',', row = line, col = current - start, value = '' }
        elseif char == '.' then
            if match('.') then
                if match('.') then
                    tokens[#tokens + 1] = { tag = '...', row = line, col = current - start, value = '' }
                else
                    tokens[#tokens + 1] = { tag = '..', row = line, col = current - start, value = '' }
                end
            else
                tokens[#tokens + 1] = { tag = '.', row = line, col = current - start, value = '' }
            end
        elseif char == ':' then
            if match(':') then
                tokens[#tokens + 1] = { tag = '::', row = line, col = current - start, value = '' }
            else
                tokens[#tokens + 1] = { tag = ':', row = line, col = current - start, value = '' }
            end
        elseif char == '!' then
            tokens[#tokens + 1] = { tag = '!', row = line, col = current - start, value = '' }
        elseif char == '=' then
            if match('=') then
                tokens[#tokens + 1] = { tag = '==', row = line, col = current - start, value = '' }
            else
                tokens[#tokens + 1] = { tag = '=', row = line, col = current - start, value = '' }
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

    tokens[#tokens + 1] = { tag = 'EOF', row = line, col = current - start, value = '' }

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

        for i = 1, #args do
            local type = args[i]
            if check(type) then
                advance()
                return true
            end
        end

        return false
    end

    local function ExpBool(value)
        return { tag = 'ExpBool', value = value }
    end

    local function ExpNil()
        return { tag = 'ExpNil' }
    end

    local function ExpNumber(value)
        return { tag = 'ExpNumber', value = value }
    end

    local function ExpNome(value)
        return { tag = 'ExpNome', value = value }
    end

    local function ExpString(value)
        return { tag = 'ExpString', value = value }
    end

    local function ExpTable(inits)
        return { tag = 'ExpTable', content = inits }
    end

    local function ExpFieldKey(key, value)
        return { tag = 'ExpFieldKey', key = key, value = value }
    end

    local function ExpIndex(table, key)
        return { tag = 'ExpIndex', table = table, key = key }
    end

    local function ExpChamada(expf, params)
        return { tag = 'ExpChamada', expf = expf, params = params }
    end

    local function ExpLuaFunc(params, body)
        return { tag = 'ExpLuaFunc', params = params, body = body }
    end

    local function ExpUnop(op, exp)
        return { tag = 'ExpUnop', op = op, exp = exp }
    end

    local function ExpBinop(op, exp1, exp2)
        return { tag = 'ExpBinop', op = op, exp1 = exp1, exp2 = exp2 }
    end

    local function ExpLogical(op, exp1, exp2)
        return { tag = 'ExpLogical', op = op, exp1 = exp1, exp2 = exp2 }
    end

    local function CmdSetVar(name, exp)
        return { tag = 'CmdSetVar', name = name, exp = exp }
    end

    local function CmdSetTbl(lhs, key, rhs)
        return { tag = 'CmdSetTbl', lhs = lhs, key = key, rhs = rhs }
    end

    local function CmdChamada(exp)
        return { tag = 'CmdChamada', exp = exp }
    end

    local function CmdReturn(exp)
        return { tag = 'CmdReturn', exp = exp }
    end

    local function CmdLocal(name, exp, bloco)
        return { tag = 'CmdLocal', name = name, exp = exp, bloco = bloco }
    end

    local function CmdWhile(condition, body)
        return { tag = 'CmdWhile', condition = condition, body = body }
    end

    local function CmdIf(condition, thenBranch, elseBranch)
        return { tag = 'CmdIf', condition = condition, thenBranch = thenBranch, elseBranch = elseBranch }
    end

    local function CmdBloco(comandos)
        return { tag = 'CmdBloco', comandos = comandos }
    end

    local function parseField()
        if match('STRING') then
            return ExpFieldKey(nil, ExpString(previous().value))
        elseif match('NOME') then
            local key = previous().value

            if match('=') then
                local value = expression()
                return ExpFieldKey(key, value)
            else
                return ExpFieldKey(nil, ExpNome(key))
            end
        elseif match('NUMBER') then
            return ExpFieldKey(nil, ExpNumber(previous().value))
        else
            reportError('Expected a field name.')
        end
    end

    local function simples()
        if match('true') then
            return ExpBool(true)
        elseif match('false') then
            return ExpBool(false)
        elseif match('nil') then
            return ExpNil()
        elseif match('NUMBER') then
            return ExpNumber(previous().value)
        elseif match('STRING') then
            return ExpString(previous().value)
        elseif match('{') then
            local inits = {}
            -- Se houver campos, preciso parsear, se não, a tabela é vazia
            if check('}') == false then
                inits[#inits + 1] = parseField()
                while match(',') do
                    if check('}') == false then
                        inits[#inits + 1] = parseField()
                    end
                end
            end
            consume('}', 'Expected "}" after table content.')
            return ExpTable(inits)
        elseif match('function') then
            consume('(', 'Expected "(" after function name.')
            local params = {}
            if check(')') == false then
                params[#params + 1] = consume('NOME', 'Expected parameter name after "(".')
                while match(',') do
                    if check(')') == false then
                        if #params > 255 then
                            reportError('Too many parameters in function declaration. Maximum is 255.')
                        end
                        params[#params + 1] = consume('NOME', 'Expected parameter name after ",".')
                    end
                end
            end

            consume(')', 'Expected ")" after function parameters.')

            local body = bloco()
            consume('end', 'Expected "end" after "function".')

            return ExpLuaFunc(params, body)
        else
            reportError('Expected a simple expression.')
        end
    end

    local function primary()
        if match('NOME') then
            return ExpNome(previous().value)
        elseif match('(') then
            local expr = expression()
            consume(')', 'Expected ")" after expression.')
            return expr
        else
            return simples()
        end
    end

    local function sufixado()
        local exp = primary()

        -- Preciso considerar várias chamadas de funções
        while match('(', '.', '[') do
            local token = previous().tag
            if token == '(' then
                local params = {}
                if check(')') == false then
                    params[#params + 1] = expression()
                    while match(',') do
                        if check(')') == false then
                            if #params > 255 then
                                reportError('Too many arguments in function call. Maximum is 255.')
                            else
                                params[#params + 1] = expression()
                            end
                        end
                    end
                end
                consume(')', 'Expected ")" after function arguments.')
                exp = ExpChamada(exp, params)
            elseif token == '[' then
                local key = expression()
                consume(']', 'Expected "]" after field.')
                exp = ExpIndex(exp, key)
            elseif token == '.' then
                local nome = consume('NOME', 'Expected field name after ".".')
                local key = ExpString(nome.value)

                exp = ExpIndex(exp, key)
            end
        end

        return exp
    end

    local function unary()
        if match('-', 'not', '#') then
            local operator = previous()
            local right = unary()
            return ExpUnop(operator.tag, right)
        end

        return sufixado()
    end

    local function factor()
        local expr = unary()

        while match('*', '/') do
            local operator = previous()
            local right = unary()
            expr = ExpBinop(operator.tag, expr, right)
        end

        return expr
    end

    local function term()
        local expr = factor()

        while match('+', '-') do
            local operator = previous()
            local right = factor()
            expr = ExpBinop(operator.tag, expr, right)
        end

        return expr
    end

    local function comparison()
        local expr = term()

        while match('>', '>=', '<', '<=', '==', '~=') do
            local operator = previous()
            local right = term()
            expr = ExpBinop(operator.tag, expr, right)
        end

        return expr
    end

    local function andLogical()
        local expr = comparison()

        while match('and') do
            local operator = previous()
            local right = comparison()
            expr = ExpLogical(operator.tag, expr, right)
        end

        return expr
    end

    local function orLogical()
        local expr = andLogical()

        while match('or') do
            local operator = previous()
            local right = andLogical()
            expr = ExpLogical(operator.tag, expr, right)
        end

        return expr
    end

    expression = function()
        return orLogical()
    end

    local function functionDeclaration()
        local name = consume('NOME', 'Expected function name after "function".')
        consume('(', 'Expected "(" after function name.')
        local params = {}
        if check(')') == false then
            params[#params + 1] = consume('NOME', 'Expected parameter name after "(".')
            while match(',') do
                if check(')') == false then
                    if #params > 255 then
                        reportError('Too many parameters in function declaration. Maximum is 255.')
                    end
                    params[#params + 1] = consume('NOME', 'Expected parameter name after ",".')
                end
            end
        end

        consume(')', 'Expected ")" after function parameters.')

        local body = bloco()
        consume('end', 'Expected "end" after "function".')

        return CmdSetVar(name.value, ExpLuaFunc(params, body))
    end

    local function localStatement()
        consume('NOME', 'Expected variable name after "local".')

        local name = previous().value
        local exp = nil

        if match('=') then
            exp = expression()
        else
            exp = ExpNil()
        end

        local bloco = bloco()

        return CmdLocal(name, exp, bloco)
    end

    local function forStatement()
        consume('NOME', 'Expected variable name after "for".')

        local name = previous().value
        consume('=', 'Expected "=" after variable name.')

        local start = expression()
        consume(',', 'Expected "," after start value.')

        local endValue = expression()
        local step = ExpNumber(1) -- Default step is 1
        if match(',') then
            step = expression()
        end

        consume('do', 'Expected "do" after "for".')

        local body = bloco()
        consume('end', 'Expected "end" after "for".')

        if step.value > 0 then
            return CmdLocal(
                name,
                start,
                CmdBloco({
                    CmdWhile(
                        ExpBinop('<=', ExpNome(name), endValue),
                        CmdBloco({
                            body,
                            CmdSetVar(name, ExpBinop('+', ExpNome(name), step))
                        })
                    )
                })
            )
        else
            -- If step is negative, we need to change the condition to check for greater than
            return CmdLocal(
                name,
                start,
                CmdBloco({
                    CmdWhile(
                        ExpBinop('>=', ExpNome(name), endValue),
                        CmdBloco({
                            body,
                            CmdSetVar(name, ExpBinop('-', ExpNome(name), step))
                        })
                    )
                })
            )
        end
    end

    local function whileStatement()
        local condition = expression()

        consume('do', 'Expected "do" after "condition".')

        local body = bloco()
        consume('end', 'Expected "end" after "while".')

        return CmdWhile(condition, body)
    end

    local function elseStatement()
        if match('end') then
            return nil
        elseif match('else') then
            local result = bloco()
            consume('end', 'Expected "end" after "else".')
            return result
        elseif match('elseif') then
            return ifStatement()
        else
            reportError('Expected "else" or "elseif".')
        end
    end

    ifStatement = function()
        local condition = expression()

        consume('then', 'Expected "then" after condition.')

        local thenBranch = bloco()
        local elseBranch = elseStatement()

        return CmdIf(condition, thenBranch, elseBranch)
    end

    comando = function()
        if match('if') then
            return ifStatement()
        elseif match('while') then
            return whileStatement()
        elseif match('for') then
            return forStatement()
        elseif match('local') then
            return localStatement()
        elseif match('function') then
            return functionDeclaration()
        elseif match('return') then
            local returnRow = previous().row
            local value = ExpNil()
            if check('EOF') == false and check('end') == false and returnRow == peek().row then
                value = expression()
            end

            return CmdReturn(value)
        else
            local exp = sufixado()

            if match('=') then
                local value = expression()

                if exp.tag == 'ExpNome' then
                    return CmdSetVar(exp.value, value)
                elseif exp.tag == 'ExpIndex' then
                    return CmdSetTbl(exp.table, exp.key, value)
                else
                    reportError('Syntax error: Invalid assignment target.')
                end
            elseif exp.tag == 'ExpChamada' then
                return CmdChamada(exp)
            end

            return exp
        end
    end

    bloco = function()
        local comandos = {}
        while check('end') == false and check('else') == false and check('elseif') == false and check('until') == false and isAtEnd() == false do
            comandos[#comandos + 1] = comando()
        end
        return CmdBloco(comandos)
    end

    return bloco()
end

local function interpreter(bloco)
    local function reportError(msg)
        io.write(string.format("Error: %s", msg))
        os.exit(1)
    end

    local function ValString(value)
        return { tag = 'ValString', value = value }
    end

    local function ValNumber(value)
        return { tag = 'ValNumber', value = value }
    end

    local function ValBool(value)
        return { tag = 'ValBool', value = value }
    end

    local function ValNil()
        return { tag = 'ValNil' }
    end

    local function ValTable(table)
        return { tag = 'ValTable', content = table }
    end

    local function ValLibFunc(arity, call)
        arity = arity or 0
        call = call or function(args)
            reportError('Cannot call a library function without implementation.')
        end

        return {
            tag = 'ValLibFunc',
            arity = arity,
            call = call
        }
    end

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

    local GLOBALS = {
        math = { pi = ValNumber(math.pi) },
    }
    GLOBALS.print = ValLibFunc(1, function(args)
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
    end)

    local evalCmd = function(statement, body) end

    local function EnvNew(key, value, enclosing)
        return { key = key, value = value, enclosing = enclosing }
    end

    local function getEnv(env, key)
        if env.key == key then
            return env.value
        elseif env.enclosing then
            return getEnv(env.enclosing, key)
        else
            local result = GLOBALS[key]
            if result == nil then
                return ValNil()
            else
                return result
            end
        end
    end

    local function assignEnv(env, key, value)
        if env.key == key then
            env.value = value
        elseif env.enclosing then
            assignEnv(env.enclosing, key, value)
        else
            GLOBALS[key] = value
        end
    end

    local function ValLuaFunc(params, body, env)
        return {
            tag = 'ValLuaFunc',
            params = params,
            closure = env,
            body = body
        }
    end

    local function callLuaFunc(func, args)
        local environment = EnvNew(nil, nil, func.closure)
        for i = 1, #func.params do
            local param = func.params[i]
            environment.key = param.value
            environment.value = args[i]

            environment = EnvNew(nil, nil, environment)
        end

        return evalCmd(func.body, environment)
    end

    local function evalExp(expr, environment)
        if expr.tag == "ExpBool" then
            return ValBool(expr.value)
        elseif expr.tag == "ExpNil" then
            return ValNil()
        elseif expr.tag == "ExpNumber" then
            return ValNumber(expr.value)
        elseif expr.tag == "ExpString" then
            return ValString(expr.value)
        elseif expr.tag == "ExpNome" then
            return getEnv(environment, expr.value)
        elseif expr.tag == "ExpLuaFunc" then
            return ValLuaFunc(expr.params, expr.body, environment)
        elseif expr.tag == "ExpUnop" then
            local valRight = evalExp(expr.exp, environment)
            if expr.op == '-' then
                checkTypeAndOperand("Number", valRight)
                return ValNumber(-valRight.value)
            elseif expr.op == 'not' then
                return ValBool(not isTruthy(valRight))
            elseif expr.op == '#' then
                if valRight.tag == 'ValString' then
                    return ValNumber(#valRight.value)
                elseif valRight.tag == 'ValTable' then
                    return ValNumber(#valRight.content)
                else
                    reportError('Cannot apply length operator to type: ' .. valRight.tag)
                end
            else
                reportError('Unknown unary operator: ' .. expr.op)
            end
        elseif expr.tag == "ExpBinop" then
            -- io.write(inspect(environment) .. '\n')
            local valLeft = evalExp(expr.exp1, environment)
            local valRight = evalExp(expr.exp2, environment)

            if expr.op == '+' then
                checkTypeAndOperand("Number", valLeft, valRight)
                return ValNumber(valLeft.value + valRight.value)
            elseif expr.op == '-' then
                checkTypeAndOperand("Number", valLeft, valRight)
                return ValNumber(valLeft.value - valRight.value)
            elseif expr.op == '*' then
                checkTypeAndOperand("Number", valLeft, valRight)
                return ValNumber(valLeft.value * valRight.value)
            elseif expr.op == '/' then
                checkTypeAndOperand("Number", valLeft, valRight)
                return ValNumber(valLeft.value / valRight.value)
            elseif expr.op == '^' then
                checkTypeAndOperand("Number", valLeft, valRight)
                return ValNumber(valLeft.value ^ valRight.value)
            elseif expr.op == '==' then
                return ValBool(isEqual(valLeft, valRight))
            elseif expr.op == '~=' then
                return ValBool(not isEqual(valLeft, valRight))
            elseif expr.op == '<' then
                checkTypeAndOperand("Number", valLeft, valRight)
                return ValBool(valLeft.value < valRight.value)
            elseif expr.op == '<=' then
                checkTypeAndOperand("Number", valLeft, valRight)
                return ValBool(valLeft.value <= valRight.value)
            elseif expr.op == '>' then
                checkTypeAndOperand("Number", valLeft, valRight)
                return ValBool(valLeft.value > valRight.value)
            elseif expr.op == '>=' then
                checkTypeAndOperand("Number", valLeft, valRight)
                return ValBool(valLeft.value >= valRight.value)
            elseif expr.op == '..' then
                checkTypeAndOperand("String", valLeft, valRight)
                return ValString(valLeft.value .. valRight.value)
            else
                return reportError('Unknown binary operator: ' .. expr.op)
            end
        elseif expr.tag == "ExpLogical" then
            local valLeft = evalExp(expr.exp1, environment)

            if expr.op == 'or' then
                if isTruthy(valLeft) then
                    return valLeft
                end
            else
                if not isTruthy(valLeft) then
                    return valLeft
                end
            end

            return evalExp(expr.exp2, environment)
        elseif expr.tag == "ExpChamada" then
            local func = evalExp(expr.expf, environment)

            local args = {}
            for i = 1, #expr.params do
                local result = evalExp(expr.params[i], environment)

                args[#args + 1] = result
            end

            if func.tag == "ValLibFunc" then
                if #args ~= func.arity then
                    reportError(string.format("Function '%s' expects %d arguments, but got %d.", expr.expf.value,
                        func.arity, #args))
                end

                return func.call(args)
            elseif func.tag == "ValLuaFunc" then
                if #args ~= #func.params then
                    reportError(string.format("Function '%s' expects %d arguments, but got %d.", expr.expf.value,
                        #func.params, #args))
                end

                return callLuaFunc(func, args)
            else
                reportError(string.format("Cannot call a value of type '%s' as a function.", func.tag))
            end
        elseif expr.tag == "ExpTable" then
            local content = {}

            for i = 1, #expr.content do
                local field = expr.content[i]

                if field.tag == 'ExpFieldKey' then
                    local value = evalExp(field.value, environment)
                    if field.key == nil then
                        content[#content + 1] = value -- se for um campo sem nome, adiciona ao final da tabela
                    else
                        content[field.key] = value
                    end
                else
                    reportError('Expected a field name.')
                end
            end

            return ValTable(content)
        elseif expr.tag == "ExpIndex" then
            local tableValue = evalExp(expr.table, environment)
            local key = evalExp(expr.key, environment)

            if tableValue.tag == 'ValTable' then
                if key.tag == 'ValString' or key.tag == 'ValNumber' then
                    return tableValue.content[key.value] or ValNil()
                else
                    reportError('Table index must be a string or number.')
                end
            else
                reportError('Expected a table for indexing.')
            end
        else
            reportError('Undefined expression.')
        end
    end

    evalCmd = function(statement, environment)
        if statement.tag == 'CmdBloco' then
            for i = 1, #statement.comandos do
                local cmd = statement.comandos[i]
                -- io.write(cmd.tag .. '\n')
                local result = evalCmd(cmd, environment)
                if result ~= nil and result.tag ~= 'ValNil' then
                    return result
                end
            end
        elseif statement.tag == 'CmdIf' then
            local condition = evalExp(statement.condition, environment)
            if condition.value then
                return evalCmd(statement.thenBranch, environment)
            else
                if statement.elseBranch then
                    return evalCmd(statement.elseBranch, environment)
                end
            end
        elseif statement.tag == 'CmdWhile' then
            local condition = evalExp(statement.condition, environment)
            while condition.value do
                local result = evalCmd(statement.body, environment)
                if result ~= nil and result.tag ~= "ValNil" then
                    return result
                end
                condition = evalExp(statement.condition, environment)
            end
        elseif statement.tag == "CmdSetVar" then
            local name = statement.name
            local rhs = evalExp(statement.exp, environment)

            assignEnv(environment, name, rhs)
        elseif statement.tag == 'CmdSetTbl' then
            local lhs = evalExp(statement.lhs, environment)
            local key = evalExp(statement.key, environment)
            local rhs = evalExp(statement.rhs, environment)

            if statement.lhs.tag == 'ExpNome' then
                lhs.content[key.value] = rhs
            else
                reportError('Expected variable name.')
            end
        elseif statement.tag == 'CmdLocal' then
            local name = statement.name
            local exp = evalExp(statement.exp, environment)

            environment.key = name
            environment.value = exp

            local result = evalCmd(statement.bloco, EnvNew(nil, nil, environment))
            return result
        elseif statement.tag == 'CmdChamada' then
            return evalExp(statement.exp, environment)
        elseif statement.tag == 'CmdReturn' then
            local result = evalExp(statement.exp, environment)
            return result
        else
            reportError('Undefined command.')
        end
    end

    return evalCmd(bloco, EnvNew(nil, nil, nil))
end

local function write_assembly(bloco)
    local labelCounter = 0
    -- local localStack = {current=1, stack={{}}}
    -- local program = {}

    -- Uma pilha de funções onde o programa principal é o primeiro
    -- e as funções aninhadas são empilhadas conforme são declaradas
    local closures = {
        current=1,
        stack={
            {
                locals={}, program={}
            }
        }
    }
    
    local genBloco = function(statement) end

    local function newLabel()
        labelCounter = labelCounter + 1
        return 'L' .. labelCounter
    end

    local function reportError(msg)
        io.write(string.format("Error: %s", msg))
        os.exit(1)
    end

    local function writeInstruction(instruction)
        local currentClosure = closures.stack[closures.current]
        local program = currentClosure.program
        program[#program + 1] = '\t' .. instruction .. '\n'
    end

    local function writeLabel(label)
        local currentClosure = closures.stack[closures.current]
        local program = currentClosure.program
        program[#program + 1] = label .. ':\n'
    end

    local function getLocal(key)
        local currentClosure = closures.stack[closures.current]
        local currentLocals = currentClosure.locals

        for idx = 1, #currentLocals do
            if currentLocals[idx] == key then
                return idx
            end
        end
    end

    local function setLocal(key)
        local currentClosure = closures.stack[closures.current]
        local currentLocals = currentClosure.locals

        for idx = 1, #currentLocals do
            if currentLocals[idx] == key then
                currentLocals[idx] = key
                return idx
            end
        end

        -- Se não encontrou, adiciona ao ambiente atual
        currentLocals[#currentLocals + 1] = key
        return #currentLocals
    end

    local function genExp(expression)
        if expression.tag == 'ExpBool' then
            if expression.value then
                writeInstruction('PUSH_TRUE')
            else
                writeInstruction('PUSH_FALSE')
            end
        elseif expression.tag == 'ExpNil' then
            writeInstruction('PUSH_NIL')
        elseif expression.tag == 'ExpNumber' then
            writeInstruction('PUSH_NUMBER ' .. expression.value)
        elseif expression.tag == 'ExpString' then
            local instruction = 'PUSH_STRING "'
            -- io.write('\tPUSH_STRING "')

            for i = 1, #expression.value do
                local char = expression.value:sub(i, i)
                -- Fazer o inverso do escape
                if char == '\\' then
                    instruction = instruction .. '\\\\'
                elseif char == '"' then
                    instruction = instruction .. '\\"'
                elseif char == '\t' then
                    instruction = instruction .. '\\t'
                elseif char == '\r' then
                    instruction = instruction .. '\\r'
                elseif char == '\v' then
                    instruction = instruction .. '\\v'
                elseif char == '\a' then
                    instruction = instruction .. '\\a'
                elseif char == '\b' then
                    instruction = instruction .. '\\b'
                elseif char == '\f' then
                    instruction = instruction .. '\\f'
                elseif char == '\n' then
                    instruction = instruction .. '\\n'
                elseif char == '\r' then
                    instruction = instruction .. '\\r'
                elseif char == '\t' then
                    instruction = instruction .. '\\t'
                elseif char == '\v' then
                    instruction = instruction .. '\\v'
                elseif char == '\0' then
                    instruction = instruction .. '\\0'
                else
                    instruction = instruction .. char
                end
            end

            instruction = instruction .. '"'
            writeInstruction(instruction)
        elseif expression.tag == 'ExpNome' then
            local idx = getLocal(expression.value)
            if idx then
                writeInstruction('GET_LOCAL ' .. idx)
            else
                writeInstruction('GET_GLOBAL ' .. expression.value)
            end
        elseif expression.tag == 'ExpLuaFunc' then
            local startClosure = closures.current
            
            -- Cria um novo ambiente para a função
            closures.current = #closures.stack + 1
            closures.stack[closures.current] = {
                locals = {},
                program = {}
            }
            
            for i = 1, #expression.params do
                local paramName = expression.params[i].value
                setLocal(paramName)
            end

            genBloco(expression.body)

            local currentClosure = closures.stack[closures.current]
            local program = currentClosure.program
            if program[#program] ~= '\tRETURN\n' then
                writeInstruction('PUSH_NIL') -- Se não houver retorno explícito, retorna nil
                writeInstruction('RETURN')
            end

            -- Retorna ao ambiente anterior
            closures.current = startClosure
            writeInstruction('PUSH_CLOSURE ' .. #closures.stack - 1)
        elseif expression.tag == 'ExpUnop' then
            genExp(expression.exp)

            if expression.op == '-' then
                writeInstruction('NEG')
            elseif expression.op == 'not' then
                writeInstruction('NOT')
            elseif expression.op == '#' then
                writeInstruction('LEN')
            else
                reportError('Unsupported unary operator: ' .. expression.op)
            end
        elseif expression.tag == 'ExpLogical' then
            genExp(expression.exp1)

            if expression.op == 'and' then
                local labelEnd = newLabel()
                writeInstruction('JUMP_FALSE ' .. labelEnd)
                genExp(expression.exp2)
                writeLabel(labelEnd)
            elseif expression.op == 'or' then
                local labelEnd = newLabel()
                writeInstruction('JUMP_TRUE ' .. labelEnd)
                genExp(expression.exp2)
                writeLabel(labelEnd)
            else
                reportError('Unsupported logical operator: ' .. expression.op)
            end
        elseif expression.tag == 'ExpBinop' then
            genExp(expression.exp1)
            genExp(expression.exp2)

            if expression.op == '+' then
                writeInstruction('ADD')
            elseif expression.op == '-' then
                writeInstruction('SUB')
            elseif expression.op == '*' then
                writeInstruction('MUL')
            elseif expression.op == '/' then
                writeInstruction('DIV')
            elseif expression.op == '%' then
                writeInstruction('MOD')
            elseif expression.op == '==' then
                writeInstruction('EQ')
            elseif expression.op == '~=' then
                writeInstruction('NEQ')
            elseif expression.op == '<' then
                writeInstruction('LT')
            elseif expression.op == '<=' then
                writeInstruction('LEQ')
            elseif expression.op == '>' then
                writeInstruction('GT')
            elseif expression.op == '>=' then
                writeInstruction('GEQ')
            elseif expression.op == '..' then
                writeInstruction('CONCAT')
            else
                reportError('Unsupported binary operator: ' .. expression.op)
            end
        elseif expression.tag == 'ExpChamada' then
            genExp(expression.expf)
            for i = 1, #expression.params do
                genExp(expression.params[i])
            end

            writeInstruction('CALL ' .. #expression.params)
        elseif expression.tag == 'ExpTable' then
            writeInstruction('NEW_TABLE')

            for i = 1, #expression.content do
                local field = expression.content[i]
                if field.tag == 'ExpFieldKey' then
                    if field.key then
                        genExp(field.key)
                        genExp(field.value)
                    else
                        writeInstruction('PUSH_NUMBER ' .. i) -- se for um campo sem nome, usa o índice
                        writeInstruction('PUSH_NUMBER ' .. field.value.value) -- o valor é um literal
                    end
                    writeInstruction('SET_TABLE')
                else
                    reportError('Expected a field key in table expression.')
                end
            end
        elseif expression.tag == 'ExpIndex' then
            genExp(expression.table)
            genExp(expression.key)
            writeInstruction('GET_TABLE')
        else
            reportError('Unsupported expression for assembly generation: ' .. expression.tag)
        end
    end

    genBloco = function (statement)
        if statement.tag == 'CmdBloco' then
            for i = 1, #statement.comandos do
                local cmd = statement.comandos[i]
                genBloco(cmd)
                if cmd.tag == 'CmdReturn' then
                    return
                end
            end
        elseif statement.tag == 'CmdIf' then
            genExp(statement.condition)

            local labelEnd = newLabel()
            local labelElse = newLabel()

            if statement.elseBranch then
                writeInstruction('JUMP_FALSE ' .. labelElse)
            else
                writeInstruction('JUMP_FALSE ' .. labelEnd)
            end

            genBloco(statement.thenBranch)
            writeInstruction('JUMP ' .. labelEnd)

            if statement.elseBranch then
                writeLabel(labelElse)
                genBloco(statement.elseBranch)
            end

            writeLabel(labelEnd)
        elseif statement.tag == 'CmdWhile' then
            local labelCond = newLabel()
            local labelBody = newLabel()
            local labelEnd = newLabel()

            writeInstruction('JUMP ' .. labelCond)

            writeLabel(labelBody)
            genBloco(statement.body)

            writeLabel(labelCond)
            genExp(statement.condition)

            writeInstruction('JUMP_TRUE ' .. labelBody)
            writeLabel(labelEnd)
        elseif statement.tag == 'CmdSetVar' then
            local name = statement.name
            genExp(statement.exp)

            local idx = getLocal(name)
            if idx then
                writeInstruction('SET_LOCAL ' .. idx)
            else
                writeInstruction('SET_GLOBAL ' .. name)
            end
        elseif statement.tag == 'CmdSetTbl' then
            genExp(statement.lhs)
            genExp(statement.key)
            genExp(statement.rhs)

            writeInstruction('SET_TABLE')
        elseif statement.tag == 'CmdLocal' then
            local name = statement.name
            genExp(statement.exp)

            local idx = setLocal(name)
            writeInstruction('SET_LOCAL ' .. idx)

            genBloco(statement.bloco)
        elseif statement.tag == 'CmdChamada' then
            genExp(statement.exp)
            writeInstruction('POP 1') -- Descartar o resultado da chamada
        elseif statement.tag == 'CmdReturn' then
            genExp(statement.exp)
            writeInstruction('RETURN')
        else
            reportError('Unsupported command for assembly generation: ' .. statement.tag)
        end
    end

    genBloco(bloco)

    -- io.write('# Program name: ' .. arg[0] .. '\n')
    io.write('# Generated by custom Lua compiler\n')
    io.write('# Author: Diego V. S. de Matos <diegovsm@ic.ufrj.br>\n')
    io.write('# Date: ' .. os.date('%d/%m/%Y - %H:%M:%S') .. '\n')
    io.write('\n')

    -- Percorre do último elemento para o primeiro
    for i = #closures.stack, 1, -1 do
        local closure = closures.stack[i]
        io.write('CLOSURE ' .. i-1)
        if i == 1 then
            io.write(' # MAIN\n')
        else
            io.write('\n')
        end

        for j=1, #closure.program do
            io.write(closure.program[j])
        end

        if i == 1 then
            io.write('\tEXIT\n')
        end

        io.write('\n')
    end
end

local function main()
    local debug = arg[1] == '-d' or arg[1] == '--debug'
    local interpreterMode = arg[2] == '-i' or arg[2] == '--interpreter'

    local source = io.read('*a')
    local tokens = lexer(source)

    if debug then
        io.write('Tokens\n')
        io.write('Row\tCol\tTokens\tValor\n')
        for i = 1, #tokens, 1 do
            local token = tokens[i]
            if token.tag == 'EOF' then
                io.write(token.row .. '\t' .. token.col .. '\t' .. 'EOF\n')
            else
                io.write(token.row .. '\t' .. token.col .. '\t' .. token.tag .. '\t' .. token.value .. '\n')
            end
        end
    end

    local statements = parser(tokens)

    if debug then
        io.write('\nArvore de Sintaxe\n')
        io.write(inspect(statements))
        io.write('\n')
    end

    if interpreterMode then
        interpreter(statements)
    else
        write_assembly(statements)
    end

    os.exit(0)
end

main()
