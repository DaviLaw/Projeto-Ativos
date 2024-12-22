# Projeto-Ativos
# Monitoramento de Ativos com Alerta por E-mail 🚀

## 📌 Visão Geral do Projeto
Este projeto realiza o **monitoramento de cotações de ativos da B3** (ex.: PETR4) e **envia alertas por e-mail** quando o preço atinge valores pré-definidos para **compra** ou **venda**.

### O que o código faz?
- Faz requisições a uma **API de cotações** (ibovfinancials.com) para buscar o preço atual de um ativo.
- A cada **60 segundos**, verifica se o preço:
  - **Subiu** acima do limite de venda (alerta de venda).
  - **Caiu** abaixo do limite de compra (alerta de compra).
- Se alguma condição for atendida, o programa **envia um e-mail de alerta**.

---
## 🔑 Configuração de E-mail e Token da API

Para que o projeto funcione corretamente, você precisa:  
1. Obter um **token de API** para acessar as cotações.  
2. Configurar uma **senha de app** no Gmail para enviar e-mails via SMTP.

---

### 📈 1. Gerar o Token da API de Cotações (IbovFinancials) e Configurar e-mails
1. Acesse o site: [https://ibovfinancials.com](https://ibovfinancials.com)  
2. Crie uma conta ou faça login.  
3. Vá até a aba **API Tokens** e clique em **Gerar Novo Token**.
5. Abra o arquivo `config/config.json`.  
6. Copie o token gerado e adicione ao arquivo `config/config.json` no lugar de "SEU_TOKEN_AQUI" no campo `ibov_token`.
7. Substitua "SEU_EMAIL" nos campos `smtp_user` e `email_from` pelo e-mail que irá realizar o envio da mensagem.
8. Substitua "EMAIL_DESTINO" no campo `email_from` pelo e-mail que irá receber a mensagem.

![img111](https://github.com/user-attachments/assets/362e47fa-feee-47ab-91d1-c67e0d017d5d)

---

### 📧 2. Configurar Senha de App (SMTP Gmail)

1. Acesse sua conta do Gmail.
2. Vá para Gerenciamento de Conta > Segurança.
3. Ative a Verificação em Duas Etapas (se ainda não estiver ativada).
4. Em seguida, vá para [Senhas de App](https://myaccount.google.com/apppasswords) e selecione "Outro (Nome Personalizado)".
5. Nomeie como Alerta Cotações e clique em Gerar.
6. Copie a senha gerada e cole no `config.json` no campo `smtp_pass`.

## 🛠️ Tecnologias Utilizadas
- **C++**
- **libcurl** (para requisições HTTP e envio de e-mails)
- **nlohmann/json** (para manipulação de JSON)
- **Threads** (para repetição a cada 60s)

---

## 📋 Requisitos



### 🔧 Dependências - **Linux (Ubuntu/Debian)**

1. **Compilador C++ (g++)**  
   ```bash
   sudo apt update
   sudo apt install build-essential

2. **libcurl (dev)**
   ```bash
   sudo apt install libcurl4-openssl-dev

3. **nlohmann/json**
   ```bash
   sudo apt install nlohmann-json-dev

4. **Git**
   ```bash
   sudo apt install git
   
---

## 📥 Clonando o Repositório
*🔹 Clonar com Git*
   ```bash
   git clone https://github.com/seuusuario/nome-do-repositorio.git
   cd nome-do-repositorio
  ```

---

## 🚧 Compilando o Projeto

  ```bash
  g++ -std=c++17 src/main.cpp src/email_sender.cpp src/config_loader.cpp -lcurl -o meu_programa

```
---
## ▶️ Executando o Programa

  ```bash
  ./meu_programa <ATIVO> <PRECO_VENDA> <PRECO_COMPRA>

```
```bash
./meu_programa PETR4 30 15

