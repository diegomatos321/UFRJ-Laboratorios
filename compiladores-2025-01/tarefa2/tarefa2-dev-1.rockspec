package = "tarefa2"
version = "dev-1"
source = {
   url = "git+https://github.com/diegomatos321/compiladores-2025-01.git"
}
description = {
   summary = "Aluno: Diego Vasconcelos Schardosim de MatosDRE: 120098723",
   detailed = [[
Aluno: Diego Vasconcelos Schardosim de Matos
DRE: 120098723]],
   homepage = "https://github.com/diegomatos321/compiladores-2025-01",
   license = "*** please specify a license ***"
}
build = {
   type = "builtin",
   modules = {
      compilador = "compilador.lua"
   }
}
