# Compatibilidade CINEMAX no PS4

## Objetivo

Priorizar a experiência CINEMAX para consoles PS4 em que o proprietário já utiliza um ambiente homebrew compatível. Os alvos iniciais solicitados são firmware 13.52 e 14.00, sem limitar a evolução a essas versões.

## Matriz de validação

| Firmware / ambiente | Prioridade | Resultado de teste |
|---|---:|---|
| 13.52 com runtime homebrew compatível | Alta | Pendente — sem teste em console |
| 14.00 com runtime homebrew compatível | Alta | Pendente — sem teste em console |
| Outras versões com runtime homebrew compatível | Alta | Pendente — validar individualmente |
| Navegador/runtime de TV | Média | Pendente |

**Importante:** firmware não é sinônimo de compatibilidade. O runtime instalado, a versão do WebKit, suporte a APIs JavaScript/CSS, permissões, resolução e método de empacotamento também contam. Não afirmaremos suporte a uma versão até executar testes reais nela.

## Requisitos de experiência

- Interface horizontal para TV, com texto legível à distância.
- Navegação completa sem mouse: setas, confirmar e voltar.
- Foco visível e movimento previsível com controle.
- Fallbacks para APIs de navegador ausentes.
- Catálogo e imagens carregados de fontes autorizadas.
- Reprodução somente por serviços e fontes com autorização para distribuição e execução no dispositivo.
- Mensagens claras quando a rede, API ou serviço de vídeo não estiver disponível.

## Estado técnico atual

O projeto atual é uma aplicação web responsiva. Ainda não é um PKG nem um aplicativo nativo PS4. O empacotamento dependerá da identificação de um runtime homebrew documentado e de uma toolchain de desenvolvimento apropriada. Os testes precisam ser feitos em hardware real, por firmware e runtime.

Este projeto não fornece instruções para desbloquear consoles, explorar vulnerabilidades ou contornar proteções. O foco é compatibilidade da aplicação em ambientes que o usuário já tenha configurado.
