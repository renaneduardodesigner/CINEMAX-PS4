# Compatibilidade CINEMAX no PS4

## Objetivo

O repositório contém duas partes distintas:

- **Aplicação web:** catálogo, pesquisa, metadados, favoritos e interface.
- **Launcher nativo homebrew:** projeto OpenOrbis em `ps4-native/`, preparado para gerar um FPKG instalável. Ao pressionar X, solicita a abertura do catálogo web no navegador do sistema.

O launcher não incorpora um motor de navegador nem um player de streaming. O catálogo web precisa estar publicado e acessível pela rede.

## Matriz de validação

| Firmware / ambiente | Prioridade | Resultado |
|---|---:|---|
| PS4 com GoldHEN e runtime compatível, firmware 13.52 | Alta | Não testado em console |
| PS4 com GoldHEN e runtime compatível, firmware 14.00 | Alta | Não testado em console |
| Outras versões com runtime homebrew compatível | Alta | Não testado; validar individualmente |
| Navegador/runtime do PS4 | Alta | Abertura externa solicitada pelo launcher; comportamento ainda não confirmado |

## Build e instalação

O workflow `.github/workflows/build-ps4-fpkg.yml` usa o container oficial OpenOrbis Toolchain v0.5.1 para compilar e empacotar o launcher. Uma execução de CI bem-sucedida deve publicar o artefato `CINEMAX-PS4-FPKG`, contendo `IV0000-CMAX00001_00-CINEMAXPS4APP000.pkg`.

A existência do workflow ou a compilação bem-sucedida não substitui o teste no console. Antes de declarar compatibilidade, instalar o pacote em um PS4 de teste e validar inicialização, vídeo, controle, abertura do navegador, rede e retorno ao launcher.

## Requisitos de experiência

- Interface horizontal para TV, com texto legível à distância.
- Navegação sem mouse: setas, confirmar e voltar.
- Foco visível e movimento previsível com controle.
- Fallbacks para APIs de navegador ausentes.
- Catálogo e imagens carregados de fontes autorizadas.
- Reprodução somente por serviços e fontes com autorização para distribuição e execução no dispositivo.
- Mensagens claras quando a rede, API ou serviço de vídeo não estiver disponível.

## Limites

Firmware não é sinônimo de compatibilidade. Runtime, versão do WebKit, serviços do sistema, permissões, APIs disponíveis, resolução e método de empacotamento também contam. Não afirmaremos suporte a uma versão até executar testes reais nela.

Este projeto não fornece instruções para desbloquear consoles, explorar vulnerabilidades ou contornar proteções. O foco é compatibilidade da aplicação em ambientes homebrew que o usuário já tenha configurado.
