<div align="center">

# <span style="color:#ed174b">CINEMAX</span> — PS4

### Seu cinema. Sua descoberta. Sua tela.

**Uma experiência de catálogo de filmes e séries, com visual premium e navegação pensada para TV.**

[![Status](https://img.shields.io/badge/status-em%20desenvolvimento-ed174b?style=for-the-badge)](#estado-do-projeto)
[![Interface](https://img.shields.io/badge/interface-HTML%20%2F%20CSS%20%2F%20JS-26364b?style=for-the-badge)](#tecnologias)
[![Plataforma](https://img.shields.io/badge/alvo-PS4-111827?style=for-the-badge)](#roadmap)

</div>

---

## ✦ Sobre o projeto

O **CINEMAX-PS4** é um projeto independente que está sendo desenvolvido para oferecer uma interface bonita, simples e confortável para descobrir filmes e séries. A experiência foi desenhada com inspiração em plataformas modernas de streaming, usando uma identidade visual própria.

> O repositório contém a interface web e um launcher nativo homebrew para PS4 em `ps4-native/`. O workflow `.github/workflows/build-ps4-fpkg.yml` compila um FPKG usando OpenOrbis Toolchain. O launcher abre o catálogo publicado no navegador do sistema; ele não incorpora um player de streaming.

## Prévia dos recursos

| Área | O que já existe |
|---|---|
| Início | Destaque visual e trilhos de filmes e séries |
| Pesquisa | Busca de filmes e séries por nome |
| Catálogo | Filtros por gênero, ordenação e paginação |
| Detalhes | Sinopse, avaliação, ano e informações do título |
| Minha lista | Favoritos salvos no dispositivo |
| Histórico | Títulos abertos recentemente |
| Descoberta | Trailer público e provedores por assinatura, grátis, com anúncios, aluguel e compra quando informados |
| Configurações | Região, conexão do catálogo e preferências |
| Navegação | Teclado, foco visível e setas para navegação em TV |
| PWA | Manifesto instalável e cache local da interface para abertura offline |

## ▶ Como abrir

1. Abra a página do repositório.
2. Entre em **index.html**.
3. Use o botão de visualização do GitHub ou publique a interface com GitHub Pages.
4. Para usar o catálogo online, abra **Configurações** no app e configure seu token de leitura do TMDb.

O app também funciona em **modo demonstração**, com títulos fictícios, sem precisar configurar uma conta.

## Aplicativo nativo para PS4 (FPKG)

O launcher homebrew está em `ps4-native/`. Ele apresenta a interface CINEMAX na TV e, ao pressionar X, solicita a abertura do catálogo web no navegador do sistema. A interface web precisa estar publicada e acessível pela rede. O pacote não contém filmes, séries ou um player incorporado.

Para gerar o pacote, abra **Actions → Build CINEMAX PS4 FPKG** e execute o workflow manualmente, ou envie um commit para `release/cinemax-0.4-hardening`. Quando a execução terminar com sucesso, baixe o artefato `CINEMAX-PS4-FPKG` na página da execução. O arquivo esperado é `IV0000-CMAX00001_00-CINEMAXPS4APP000.pkg`.

**Atenção:** a compilação automatizada confirma apenas que o FPKG foi construído. A instalação e a abertura ainda precisam ser verificadas em um PS4 real com GoldHEN. O lançamento do navegador depende dos serviços disponíveis no firmware/runtime.

## Catálogo online — TMDb

O TMDb fornece metadados, imagens e resultados de pesquisa; não fornece os arquivos dos filmes. O uso gratuito da API é destinado a projetos não comerciais e exige atribuição conforme as regras oficiais. Projetos comerciais precisam consultar o TMDb para licenciamento. As imagens e dados também podem ter direitos próprios; não presuma que possam ser redistribuídos livremente. Para habilitar:

1. Crie sua própria credencial de API no site oficial do TMDb.
2. No CINEMAX, abra **Configurações → Conectar catálogo TMDb**.
3. Cole o token de leitura e salve.

**Atenção:** não coloque tokens, senhas ou chaves em arquivos do repositório, commits, capturas de tela ou mensagens públicas. O protótipo guarda o token somente no armazenamento local do navegador. Para uma versão distribuída ao público, será necessária uma arquitetura de autenticação mais segura.

- Documentação: https://developer.themoviedb.org/docs
- Configurações da API: https://www.themoviedb.org/settings/api

Este produto usa a API do TMDb, mas não é endossado nem certificado pelo TMDb. Consulte os requisitos oficiais de atribuição, incluindo o uso da marca TMDb, antes de publicar uma versão final.

## Fontes de disponibilidade e streaming

O detalhe de cada título consulta os provedores informados pelo endpoint oficial de disponibilidade do TMDb e separa assinatura, gratuito, anúncios, aluguel e compra. O link de destino é o link de consulta regional fornecido pelos dados do TMDb. Isso é uma indicação de onde procurar o título, não uma transmissão dentro do CINEMAX.

- **TMDb:** metadados, imagens, pesquisa e disponibilidade por região; não entrega arquivos de vídeo.
- **JustWatch:** a disponibilidade apresentada pelo TMDb pode apontar para a página regional de consulta. Uma integração direta depende de parceria/API e autorização.
- **Plex:** possível fonte a avaliar, mas não há integração ativa nem garantia de catálogo ou disponibilidade no Brasil.
- **Tomato / Tomato Anime TV:** não foi localizada documentação pública verificável de API oficial para integração; nenhum conector está ativo.
- **Tela Brasil:** pode ser apresentada como destino externo de catálogo nacional; não existe player incorporado nem integração de reprodução confirmada.

O estado das fontes e os requisitos do player estão em `docs/STREAMING-SOURCES.md`. O CINEMAX não coleta credenciais de serviços de terceiros nem tenta contornar DRM, assinatura, região ou controles de acesso.

## Publicação e validação automática

O workflow em `.github/workflows/deploy-pages.yml` verifica a sintaxe JavaScript e a presença dos arquivos essenciais. Depois, tenta publicar o site no GitHub Pages automaticamente. A primeira publicação pode exigir que o proprietário habilite GitHub Pages nas configurações do repositório.

O service worker armazena apenas os arquivos da interface no mesmo domínio; chamadas ao TMDb e imagens externas não são armazenadas por ele.

## Estrutura

```text
CINEMAX-PS4/
├── index.html
├── assets/
│   ├── app.js
│   ├── styles.css
│   └── icon.svg
├── manifest.webmanifest
├── service-worker.js
├── .github/workflows/
│   └── deploy-pages.yml
├── docs/
│   ├── ARCHITECTURE.md
│   └── STREAMING-SOURCES.md
├── integrations/
│   └── seekee/STATUS.md
├── frontend/                 # Protótipo inicial preservado
├── ps4/                      # Notas de compatibilidade
└── README.md
```

## Roadmap

- [x] Identidade visual e layout responsivo
- [x] Catálogo de demonstração
- [x] Busca e filtros de catálogo
- [x] Favoritos e histórico local
- [x] Conector opcional de metadados TMDb
- [x] Detalhes e consulta de provedores separados por modalidade (assinatura, grátis, anúncios, aluguel e compra)
- [x] Aviso explícito de que idioma/dublagem não é confirmado pelos dados de provedores
- [x] Link para a página regional de disponibilidade informada pelo TMDb
- [x] Navegação básica por teclado/setas
- [ ] Testes em PS4 desbloqueados com firmwares-alvo 13.52, 14.00 e outras versões suportadas pelo ambiente homebrew do usuário
- [ ] Integração com serviços de streaming somente após API/parceria oficial e autorização
- [ ] Player integrado para títulos próprios ou licenciados, com fontes de vídeo e legendas autorizadas
- [ ] Confirmação de idioma de áudio e legendas em português brasileiro a partir de dados oficiais
- [ ] Adaptar a interface a um runtime homebrew compatível, com detecção de recursos e fallback para WebKit antigo
- [ ] Compilar e testar um pacote PS4 em ambiente de desenvolvimento adequado

## Aviso importante

O CINEMAX não hospeda, distribui nem desbloqueia filmes ou séries. A reprodução só poderá ser adicionada por meio de fontes legais e autorizadas. A disponibilidade indicada por provedores é informativa e pode mudar conforme a região e o serviço.

**Feito para evoluir, com cuidado em cada detalhe.**
