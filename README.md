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

## 🛠️ Tecnologias Utilizadas
- **C++ (C++11 ou superior)**
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

### 🔧 Dependências - **Windows**
1. **MinGW ou Visual Studio (compilador C++).**

2. **libcurl para Windows:**
   ```bash
   Baixe em https://curl.se/windows/ e configure curl.h e as bibliotecas (.lib/.dll).
   
3. **nlohmann/json: Para minGw e VScode**
   Baixe o vcpkg 
   ```bash
   git clone https://github.com/microsoft/vcpkg.git
   cd vcpkg
   .\bootstrap-vcpkg.bat

  Instale a biblioteca
   ```bash
    vcpkg install nlohmann-json

