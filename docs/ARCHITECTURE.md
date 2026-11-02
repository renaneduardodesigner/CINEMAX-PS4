# Arquitetura CINEMAX

## Camadas
- **Interface:** HTML, CSS e JavaScript sem dependências externas obrigatórias.
- **Catálogo:** modo demonstração local ou API do TMDb com token de leitura configurado pelo usuário.
- **Dados locais:** favoritos, histórico e região salvos no armazenamento do navegador.
- **Provedores:** consulta informativa de disponibilidade por região via TMDb, com link para o serviço oficial quando fornecido.
- **Integrações:** adaptadores isolados; Seekee permanece pendente de documentação oficial.

## Recursos implementados
- Início com trilhos de tendências, filmes e séries.
- Busca multi-categoria, filtro por gênero, ordenação e paginação.
- Detalhes, sinopse, avaliação, trailer público do YouTube e provedores oficiais quando disponíveis.
- Favoritos, histórico e configurações.
- Foco por teclado e setas para navegação em telas de TV.

## Segurança e limites
O token é armazenado localmente no navegador; não o publique em repositórios ou capturas de tela. Para uma distribuição pública em escala, a autenticação deverá migrar para um backend seguro ou outra arquitetura aprovada pelo provedor. O protótipo não hospeda vídeos, não contorna DRM e não fornece conteúdo sem autorização.

## Portabilidade PS4
A interface web ainda precisa ser testada no navegador/runtime específico do console. A criação de PKG exige toolchain de desenvolvimento PS4 e testes reais; esta versão não é um PKG instalável.
