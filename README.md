# IRC - Internet Relay Chat

Este projeto é uma implementação simples de um chat em terminal utilizando o modelo cliente-servidor, inspirado no conceito de IRC (Internet Relay Chat). O funcionamento se dá por meio de conexões TCP, onde múltiplos clientes podem se conectar a um servidor central e trocar mensagens em um canal de conversa comum.

A aplicação é composta por três módulos principais: Servidor, Cliente e o MSG. O servidor é responsável por aceitar conexões, controlar o número de usuários ativos e distribuir as mensagens recebidas de cada cliente para todos os demais conectados. Cada cliente, por sua vez, possui dois processos paralelos: um para envio e outro para recebimento de mensagens. Para tornar a interface mais organizada e não misturar entrada com saída de dados, o cliente lança automaticamente uma nova janela de terminal chamada MSG. Essa janela é destinada apenas à digitação de mensagens, deixando a interface principal limpa para exibição do conteúdo recebido.

O código foi desenvolvido em C++ utilizando a biblioteca padrão POSIX para manipulação de sockets e threads. A reconexão automática também foi implementada para garantir que, em caso de queda do servidor, o cliente tenha a opção de tentar se reconectar.

# Dependências do Projeto

Este projeto é multiplataforma e pode ser compilado tanto em **Linux** quanto em **Windows**.  
A seguir estão listadas todas as ferramentas.

## Ferramentas
- Compilador C++ com suporte a C++23 (ex.: `g++`, `clang++`)
- Make

## Observações

Todas as bibliotecas e headers mencionados são nativos do sistema operacional.
Se algum deles não estiver presente:

No Linux, utilize o gerenciador de pacotes da sua distribuição para instalar os pacotes de desenvolvimento correspondentes.

No Windows, verifique se o MinGW, Visual Studio Build Tools ou MSYS2 está corretamente instalado, pois já inclui todas as bibliotecas necessárias, caso precise atualize-os ou instale os respectivos programas.

## Como compilar e executar

Este projeto utiliza um Makefile. Para compilar cada programa do projeto, basta executar o comando abaixo na raiz do repositório do processo:

-`make` para compilar.

-`make run` para executar em localhost.

-`make run ARGS="IPv4 PORT"` para executar com um IP e PORT da sua preferência.

-`make clean` para limpar objects e bin.


## Funcionamento

Ao iniciar o servidor, ele cria um socket TCP que escuta em uma porta local (`127.0.0.1:2569`). Ele permite até 8 conexões simultâneas. Cada vez que um cliente se conecta, o servidor o adiciona à lista de usuários online e começa a retransmitir todas as mensagens recebidas para todos os clientes conectados.

O cliente, ao ser iniciado, primeiramente estabelece um servidor local em outra porta, que servirá como ponto de entrada para o MSG. Em seguida, tenta se conectar ao servidor principal. Uma vez conectado, o cliente lança uma nova janela de terminal com o MSG rodando.

No cliente, duas threads são iniciadas: uma para escutar o servidor e outra para enviar mensagens digitadas no MSG. O MSG é essencialmente um terminal interativo simples, onde o usuário insere suas mensagens e comandos.

### Config.hpp
Os parâmetros principais do sistema, como IP, portas, quantidade máxima de usuários e tamanho das mensagens, podem ser configurados no arquivo config.hpp, localizado no diretório Config. Abaixo está um exemplo das diretivas definidas nesse cabeçalho:

```
#define MAX_CTR 50                     // Tamanho máximo das mensagens
#define IP_SERVER_HOST "127.0.0.1"     // Endereço IP do servidor
#define PORT_SERVER_HOST 2569          // Porta do servidor
#define MAX_USERS 8                    // Número máximo de conexões simultâneas
```

## Servidor

O servidor por padrão irá aceitar conexões de até 8 usuários mas facilmente configurável pelo header `config.hpp` . Quando o limite é atingido, novas tentativas de conexão são recusadas com uma mensagem de "FULL SERVER". O servidor pode ser encerrado manualmente através de um comando digitado no terminal onde ele está rodando.

### Comandos

- `/end`: encerra o servidor e fecha todas as conexões ativas.

## Cliente

O cliente se conecta ao servidor e lança automaticamente a interface MSG para entrada de mensagens. Ele possui suporte a reconexão automática caso o servidor caia ou a conexão seja perdida.

### Comandos (via MSG)

- `/end`: encerra a conexão com o servidor e fecha o cliente.
- `/rec`: tenta reconectar ao servidor caso ele esteja offline.
