--[[
    Compiladores 2025-01 Tarefa 1
    Aluno: Diego Vasconcelos Schardosim de Matos
    DRE: 120098723
    Data: 09/04/2025
]]

-- CONSTANTES

local operators = {
    ["+"] = true,
    ["-"] = true,
    ["*"] = true,
    ["/"] = true,
    ["%"] = true,
    ["^"] = true,
    ["#"] = true,
    ["=="] = true,
    ["~="] = true,
    ["<="] = true,
    [">="] = true,
    ["<"] = true,
    [">"] = true,
    ["="] = true,
    ["("] = true,
    [")"] = true,
    ["{"] = true,
    ["}"] = true,
    ["["] = true,
    ["]"] = true,
    [";"] = true,
    [":"] = true,
    [","] = true,
    ["."] = true,
    [".."] = true,
    ["..."] = true,
    ["::"] = true,
    ["&"] = true,
    ["~"] = true,
    ["|"] = true,
    ["<<"] = true,
    [">>"] = true,
    ["//"] = true,
}

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

local validIndentifiers = {
    ["$"] = false, ["@"] = false, ["%"] = false,
}

--

local tokens = {}
local row = 1
local col = 0

local function getChar()
    local nextChar = io.read(1)
    if nextChar == "\n" then
        row = row + 1
        col = 0
    else
        col = col + 1
    end

    return nextChar
end

local function printError(msg)
    io.write(string.format("Erro (%d:%d): %s\n", row, col, msg))
    os.exit(1)
end

local function isSpace(token)
    return token == " " or token == "\t" or token == "\r"
end

local function skipSimpleComment()
    while true do
        local current = getChar()

        if current == "\n" or current == nil then
            break
        end
    end
end

local function skipMultilineComment()
    while true do
        local current = getChar()

        if current == nil then
            break
        end

        if current == "]" then
            local nextChar = getChar()

            if nextChar == "]" then
                break
            end
        end
    end
end

local function readString(startQuote)
    local buffer = ""

    while true do
        local current = getChar()
        if current == nil then
            printError("String sem fechamento de aspas")
        end

        if current == startQuote then
            break
        end

        if current == "\\" then
            local nextChar = getChar()
            if nextChar == nil then
                printError("String sem fechamento de aspas")
            end

            if nextChar == "\\" then
                buffer = buffer .. "\\"
            elseif nextChar == "\"" then
                buffer = buffer .. "\""
            elseif nextChar == "t" then
                buffer = buffer .. "\t"
            elseif nextChar == "r" then
                buffer = buffer .. "\r"
            elseif nextChar == "n" then
                buffer = buffer .. "\n"
            else
                printError("Caractere de escape invalido")
            end
        else
            buffer = buffer .. current
        end
    end

    return buffer
end

local function printTokens(tokens)
    io.write("Row\tCol\tTokens\tValor")
    for _, token in ipairs(tokens) do
        if token.tag == "EOF" then
            io.write(token.row .. "\t" .. token.col .. "\t" .. "EOF\n")
        else
            io.write(token.row .. "\t" .. token.col .. "\t" .. token.tag .. "\t" .. token.value .. "\n")
        end
    end
end

local function parseToken(token, startRow, startCol)
    if keywords[token] then
        table.insert(tokens, {tag = token, value = "", row=startRow, col=startCol})
    elseif tonumber(token) then
        table.insert(tokens, {tag = "number", value = tonumber(token), row=startRow, col=startCol})
    else
        local buffer = ""
        
        for i = 1, string.len(token) do
            local c = token:sub(i, i)

            if operators[c] then
                parseToken(buffer, startRow, startCol)
                table.insert(tokens, {tag = c, value = "", row=startRow, col=startCol})
                buffer = ""
            else
                buffer = buffer .. c
            end
        end
        
        table.insert(tokens, {tag = "nome", value = buffer, row=startRow, col=startCol})
    end
end

local function lexer(buffer, startRow, startCol)
    local current = getChar()
    if current == nil then
        table.insert(tokens, { tag = "EOF", value = "", row = row, col = col })
        return
    end

    if current == "-" then
        local buffer = current
        local nextChar = getChar()

        if nextChar == nil then
            table.insert(tokens, { tag = "EOF", value = "", row = row, col = col })
            return
        end

        if nextChar == "-" then
            local next2Char = getChar()
            if next2Char == nil then
                table.insert(tokens, { tag = "EOF", value = "", row = row, col = col })
                return
            end

            if next2Char == "[" then
                local next3Char = getChar()
                if next3Char == nil then
                    table.insert(tokens, { tag = "EOF", value = "", row = row, col = col })
                    return
                end

                if next3Char == "[" then
                    skipMultilineComment()
                    lexer("", row, col + 1)
                else
                    skipSimpleComment()
                    lexer("", row, col + 1)
                end
            else
                skipSimpleComment()
                lexer("", row, col + 1)
            end
        else
            buffer = buffer .. nextChar
            lexer(buffer, row, col + 1)
        end
    elseif current == "\"" or current == "'" then
        local buffer = readString(current)

        table.insert(tokens, { tag = "string", value = buffer, row = startRow, col = startCol })
        lexer("", row, col + 1)
    elseif tonumber(current) then
        local numberBuffer = buffer .. current
        local nextChar = getChar()

        if nextChar == nil then
            if string.len(numberBuffer) > 0 then
                parseToken(numberBuffer, startRow, startCol)
            end

            table.insert(tokens, { tag = "EOF", value = "", row = row, col = col })
            return
        elseif nextChar == "X" then
            local hexBuffer = numberBuffer .. nextChar
            while true do
                local hexChar = getChar()
                if hexChar == nil or hexChar == "\n" or isSpace(hexChar) then
                    break
                end

                hexBuffer = hexBuffer .. hexChar
            end

            if tonumber(hexBuffer) then
                table.insert(tokens, {tag = "number", value = tonumber(hexBuffer), row=startRow, col=startCol})
                lexer("", row, col + 1)
            else
                printError("Hexadecimal inválido")
            end
        else
            numberBuffer = numberBuffer .. nextChar
            lexer(numberBuffer, startRow, startCol)
        end
    elseif current == "\n" or isSpace(current) then
        if string.len(buffer) > 0 then
            parseToken(buffer, startRow, startCol)
        end

        lexer("", row, col + 1)
    elseif operators[current] then
        if string.len(buffer) > 0 then
            parseToken(buffer, startRow, startCol)
        end

        --[[ local nextChar = getChar()
        if nextChar == nil then
        elseif operators[nextChar] then
            if nextChar == "\n" or isSpace(nextChar) then
                table.insert(tokens, { tag = current, value = "", row = startRow, col = startCol })
            elseif current == "=" and nextChar == "=" then
                table.insert(tokens, { tag = "==", value = "", row = startRow, col = startCol })
            elseif current == "~" and nextChar == "=" then
                table.insert(tokens, { tag = "~=", value = "", row = startRow, col = startCol })
            elseif current == "<" and nextChar == "=" then
                table.insert(tokens, { tag = "<=", value = "", row = startRow, col = startCol })
            elseif current == ">" and nextChar == "=" then
                table.insert(tokens, { tag = ">=", value = "", row = startRow, col = startCol })
            elseif current == "<" and nextChar == "<" then
                table.insert(tokens, { tag = "<<", value = "", row = startRow, col = startCol })
            elseif current == ">" and nextChar == ">" then
                table.insert(tokens, { tag = ">>", value = "", row = startRow, col = startCol })
            elseif current == "/" and nextChar == "/" then
                table.insert(tokens, { tag = "//", value = "", row = startRow, col = startCol })
            elseif current == "." and nextChar == "." then  
                local next2Char = getChar()
                if next2Char == "." then
                    table.insert(tokens, { tag = "...", value = "", row = startRow, col = startCol })
                else
                    table.insert(tokens, { tag = "..", value = "", row = startRow, col = startCol })
                    return
                end
            else
                printError("Operador inválido")
            end
        else
        end ]]
        
        table.insert(tokens, { tag = current, value = "", row = startRow, col = startCol })
        lexer("", row, col + 1)
    else
        lexer(buffer .. current, startRow, startCol)
    end
end

local function main()
    lexer("", 1, 1)
    printTokens(tokens)
end

main()
