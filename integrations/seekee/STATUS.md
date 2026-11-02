# Estado da integração Seekee

**Situação: não conectada — aguardando confirmação técnica do fornecedor.**

A descrição pública do Seekee para filmes e séries informa que o produto funciona como guia de descoberta, usa dados do TMDb e não hospeda nem transmite vídeos. Até esta revisão, não foi localizada documentação pública de API para integrar o Seekee como catálogo ou serviço de reprodução de terceiros.

O CINEMAX mantém este ponto de integração separado para que um conector oficial possa ser implementado se o fornecedor disponibilizar:
- documentação de API e termos de uso;
- método autorizado de autenticação;
- endpoints para catálogo e, se aplicável, disponibilidade de reprodução;
- autorização para uso em aplicativo de terceiros.

Não serão usados scraping de áreas privadas, credenciais de usuário, endpoints não documentados nem mecanismos para contornar proteção de conteúdo.

Enquanto isso, a busca e os metadados podem ser fornecidos pelo TMDb, configurado pelo próprio usuário no menu Configurações. O TMDb é fonte de metadados, não de arquivos de vídeo.
