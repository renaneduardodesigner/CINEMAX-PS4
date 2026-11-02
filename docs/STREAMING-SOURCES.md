# CINEMAX — fontes de catálogo, disponibilidade e reprodução

Atualizado: 2026-11-02

## Objetivo

O CINEMAX reúne descoberta de títulos e informações sobre onde assistir. A reprodução dentro do aplicativo só deve ser habilitada para vídeos próprios, licenciados ou fornecidos por uma API/player oficial do titular dos direitos.

## Fontes avaliadas

| Fonte | Uso possível | Situação |
|---|---|---|
| TMDb | Metadados, imagens, pesquisa, provedores por região | Integrado para catálogo e disponibilidade |
| JustWatch | Descoberta de serviços e links regionais | Referência via dados de disponibilidade; API direta depende de parceria |
| Plex | Possível destino de streaming ou biblioteca pessoal | Não integrado; requer avaliação de API, direitos, país e compatibilidade |
| Tomato / Tomato Anime TV | Possível catálogo de nicho | API oficial pública não verificada; sem integração |
| Tela Brasil | Descoberta de obras nacionais | Pode ser link externo; sem reprodução incorporada confirmada |

## O que o código já faz

O detalhe do título chama o endpoint `/{movie|tv}/{id}/watch/providers` e exibe, quando retornados para a região escolhida:

- Incluído na assinatura (`flatrate`)
- Gratuito (`free`)
- Com anúncios (`ads`)
- Aluguel (`rent`)
- Compra (`buy`)

O destino regional usa o campo `link` retornado pelo TMDb. Isso é uma indicação de onde procurar o título, não uma transmissão dentro do CINEMAX.

## Português brasileiro

Idioma original, idioma da interface, áudio dublado e legendas são metadados diferentes. O parâmetro `language=pt-BR` pede textos localizados ao TMDb; não prova que o filme tenha áudio ou legenda em português brasileiro. A interface informa essa limitação e orienta a confirmar no serviço de destino.

## Player integrado — requisitos antes de implementar

1. Fonte de vídeo entregue por titular, distribuidor ou provedor com autorização explícita.
2. Documentação oficial de API/SDK e regras de incorporação.
3. URLs de streaming temporárias e seguras, se o provedor usar esse modelo.
4. Direitos territoriais e janela de exibição para o Brasil.
5. Metadados confirmados de áudio e legendas pt-BR.
6. Compatibilidade com codecs, DRM e WebKit do dispositivo-alvo.
7. Testes de reprodução, retomada, áudio, legendas, rede e controle remoto.

Não incorporar players por scraping, não extrair URLs ocultas, não compartilhar contas, não contornar DRM, paywall, assinatura, restrição regional ou controles de acesso.

## PS4

A interface web atual não é um PKG nativo. A compatibilidade precisa ser validada em hardware real e no ambiente homebrew permitido. Serviços comerciais podem depender de DRM e APIs ausentes no navegador/runtime do PS4; não prometer compatibilidade só com base no firmware. Alvos 13.52 e 14.00 continuam como testes pendentes.

## Próximas etapas

- Obter documentação e autorização de uma fonte de reprodução.
- Criar adaptador separado por provedor, sem credenciais de terceiros no frontend.
- Implementar player HTML5/HLS somente quando o formato e a licença permitirem.
- Implementar seleção de áudio/legenda usando faixas efetivamente fornecidas pela fonte.
- Fazer testes reais em celulares, TVs e PS4 antes de marcar como compatível.
