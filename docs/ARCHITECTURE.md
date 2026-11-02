# Arquitetura CINEMAX

## Camadas
- **Interface web:** HTML, CSS e JavaScript sem dependências externas obrigatórias.
- **Catálogo:** modo demonstração local ou API do TMDb com token de leitura configurado pelo usuário.
- **Dados locais:** favoritos, histórico e região salvos no armazenamento do navegador.
- **Provedores:** consulta informativa de disponibilidade por região via TMDb, com link para o serviço oficial quando fornecido.
- **Launcher PS4:** aplicação nativa homebrew em C++ construída com OpenOrbis Toolchain, localizada em `ps4-native/`.

## Recursos implementados
- Início com trilhos de tendências, filmes e séries.
- Página Descobrir integrada, com tendências semanais e rota interna `?page=descobrir`.
- Deep links internos para Início, Descobrir e Minha lista a partir do launcher PS4.
- Busca multi-categoria, filtro por gênero, ordenação e paginação.
- Detalhes, sinopse, avaliação, trailer público do YouTube e provedores oficiais quando disponíveis.
- Favoritos, histórico e configurações.
- Foco por teclado e setas para navegação em telas de TV.
- Launcher nativo com interface 2D e navegação básica pelo controle do PS4.
- Workflow de CI para compilar e empacotar o launcher como FPKG.

## Launcher e empacotamento PS4

O launcher apresenta uma tela nativa e solicita ao serviço do sistema a abertura do catálogo web no navegador do PS4. O catálogo precisa estar publicado e acessível pela rede. O launcher não contém um navegador próprio, não incorpora um player de vídeo e não inclui conteúdo audiovisual.

O workflow `.github/workflows/build-ps4-fpkg.yml` usa o container oficial OpenOrbis Toolchain v0.5.1. A execução só deve ser considerada concluída quando compilar o `eboot.bin`, criar o pacote `IV0000-CMAX00001_00-CINEMAXPS4APP000.pkg` e publicar o artefato `CINEMAX-PS4-FPKG`.

A compilação automatizada não comprova compatibilidade com todos os firmwares. Inicialização, saída de vídeo, controle, chamada do navegador e rede ainda precisam ser testados em hardware real e documentados em `ps4/COMPATIBILITY.md`.

## Segurança e limites

O token do TMDb é armazenado localmente no navegador; não o publique em repositórios ou capturas de tela. Para uma distribuição pública em escala, a autenticação deverá migrar para um backend seguro ou outra arquitetura aprovada pelo provedor.

O projeto não hospeda vídeos, não contorna DRM e não fornece conteúdo sem autorização. A disponibilidade indicada por provedores é informativa e pode mudar conforme região e serviço.

## Portabilidade

A interface web e o launcher nativo são componentes separados. O launcher depende dos serviços e APIs disponíveis no runtime/firmware de destino para abrir o navegador do sistema. O catálogo web depende da compatibilidade do navegador, incluindo suporte a APIs JavaScript/CSS, rede e armazenamento local.

Os alvos iniciais são firmware 13.52 e 14.00 em ambientes homebrew compatíveis, mas nenhum deles deve ser marcado como suportado sem teste real. Consulte a matriz em `ps4/COMPATIBILITY.md`.
