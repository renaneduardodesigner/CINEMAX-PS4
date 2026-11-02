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

> Esta versão já contém uma interface web navegável e integração opcional com metadados do TMDb. Ainda não é um aplicativo nativo de PS4 e não gera um arquivo PKG.

## Prévia dos recursos

| Área | O que já existe |
|---|---|
| Início | Destaque visual e trilhos de filmes e séries |
| Pesquisa | Busca de filmes e séries por nome |
| Catálogo | Filtros por gênero, ordenação e paginação |
| Detalhes | Sinopse, avaliação, ano e informações do título |
| Minha lista | Favoritos salvos no dispositivo |
| Histórico | Títulos abertos recentemente |
| Descoberta | Trailer público e consulta informativa de provedores quando disponíveis |
| Configurações | Região, conexão do catálogo e preferências |
| Navegação | Teclado, foco visível e setas para navegação em TV |

## ▶ Como abrir

1. Abra a página do repositório.
2. Entre em **index.html**.
3. Use o botão de visualização do GitHub ou publique a interface com GitHub Pages.
4. Para usar o catálogo online, abra **Configurações** no app e configure seu token de leitura do TMDb.

O app também funciona em **modo demonstração**, com títulos fictícios, sem precisar configurar uma conta.

## Catálogo online — TMDb

O TMDb fornece metadados, imagens e resultados de pesquisa; não fornece os arquivos dos filmes. Para habilitar:

1. Crie sua própria credencial de API no site oficial do TMDb.
2. No CINEMAX, abra **Configurações → Conectar catálogo TMDb**.
3. Cole o token de leitura e salve.

**Atenção:** não coloque tokens, senhas ou chaves em arquivos do repositório, commits, capturas de tela ou mensagens públicas. O protótipo guarda o token somente no armazenamento local do navegador. Para uma versão distribuída ao público, será necessária uma arquitetura de autenticação mais segura.

- Documentação: https://developer.themoviedb.org/docs
- Configurações da API: https://www.themoviedb.org/settings/api

Este produto usa a API do TMDb, mas não é endossado nem certificado pelo TMDb.

## Integração Seekee

A integração está mapeada em `integrations/seekee/STATUS.md`. Ainda não está conectada: precisamos de documentação e autorização oficial para qualquer integração de terceiros. O CINEMAX não presume endpoints, não acessa contas privadas e não contorna proteção de conteúdo.

## Estrutura

```text
CINEMAX-PS4/
├── index.html                 # Aplicativo web principal
├── assets/
│   ├── app.js                 # Busca, catálogo e interações
│   ├── styles.css             # Identidade visual responsiva
│   └── icon.svg               # Ícone CINEMAX
├── docs/
│   └── ARCHITECTURE.md        # Arquitetura e decisões técnicas
├── integrations/
│   └── seekee/
│       └── STATUS.md          # Situação da integração Seekee
├── frontend/                  # Protótipo inicial
├── ps4/                       # Notas de compatibilidade
└── README.md
```

## Roadmap

- [x] Identidade visual e layout responsivo
- [x] Catálogo de demonstração
- [x] Busca e filtros de catálogo
- [x] Favoritos e histórico local
- [x] Conector opcional de metadados TMDb
- [x] Detalhes e consulta informativa de provedores
- [x] Navegação básica por teclado/setas
- [ ] Testes de compatibilidade em navegador de TV/PS4
- [ ] Integração Seekee, caso exista API pública e autorizada
- [ ] Adaptar a interface a um runtime homebrew compatível
- [ ] Compilar e testar um pacote PS4 em ambiente de desenvolvimento adequado

## Aviso importante

O CINEMAX não hospeda, distribui nem desbloqueia filmes ou séries. A reprodução só poderá ser adicionada por meio de fontes legais e autorizadas. A disponibilidade indicada por provedores é informativa e pode mudar conforme a região e o serviço.

**Feito para evoluir, com cuidado em cada detalhe.**
