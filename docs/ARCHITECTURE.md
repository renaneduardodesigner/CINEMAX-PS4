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


## Matriz de compatibilidade PS4 (alvo de desenvolvimento)

O objetivo do projeto é oferecer a mesma experiência CINEMAX em instalações homebrew de PS4, incluindo os ambientes informados pelo usuário para firmware 13.52 e 14.00, além de outras versões nas quais o próprio usuário já disponha de um runtime homebrew compatível. A versão do firmware, isoladamente, não garante compatibilidade: navegador, WebKit, runtime, permissões, APIs disponíveis, método de empacotamento e ambiente instalado também influenciam.

| Ambiente | Prioridade | Situação atual |
|---|---:|---|
| PS4 homebrew com firmware 13.52 | Alta | Alvo solicitado; ainda não testado em console |
| PS4 homebrew com firmware 14.00 | Alta | Alvo solicitado; ainda não testado em console |
| Outras versões com runtime homebrew compatível | Alta | Meta de portabilidade; validar uma a uma |
| Navegador de TV / desktop | Média | Interface web responsiva; testes reais pendentes |
| Celular e tablet | Alta | CSS responsivo; testes em dispositivos reais pendentes |

### Estratégia de compatibilidade

1. Manter uma base web progressiva com HTML, CSS e JavaScript sem dependências pesadas.
2. Evitar depender exclusivamente de APIs recentes; detectar recursos antes de usá-los e fornecer alternativas quando possível.
3. Preparar uma camada de entrada para controle remoto/controle de jogo: setas, confirmar, voltar e foco visível, sem exigir mouse.
4. Oferecer layout de TV em paisagem, tipografia legível à distância e alvos de foco grandes.
5. Separar o catálogo e os metadados da reprodução de vídeo. Cada serviço de reprodução precisará de integração autorizada e compatível com o dispositivo.
6. Criar builds e configurações por runtime somente depois de identificar o ambiente homebrew e validar suas APIs documentadas.
7. Registrar testes por firmware, runtime, resolução e dispositivo; não marcar uma versão como compatível sem teste real.

### Limites e transparência

Este repositório ainda contém uma aplicação web, não um pacote PS4 instalável. Não existe neste momento uma matriz de firmwares certificados, nem teste confirmado em 13.52 ou 14.00. A criação de um pacote e sua validação exigem toolchain de desenvolvimento apropriada e testes no hardware. Este documento não contém instruções para desbloqueio, exploração de vulnerabilidades ou contorno de proteções.
