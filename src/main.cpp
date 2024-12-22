#include <iostream>
#include <curl/curl.h>
#include <thread>
#include <chrono>
#include <string>
#include <nlohmann/json.hpp>
#include "email_sender.h"
#include "config_loader.h"

using namespace std;
using json = nlohmann::json;

// Callback para escrever a resposta da API na string "output"
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}


int main(int quantidade, char* args[]) {

    string  symbol = args[1];
    double LimiteParaVender = stod(args[2]);
    double LimiteParaComprar = stod(args[3]);

    cout << symbol << endl;
    curl_global_init(CURL_GLOBAL_DEFAULT);

    CURL* curl;
    CURLcode res;
    string read;

    EmailConfig emailConfig = loadEmailConfig("config/config.json");

    //Inicializando a curl
    curl = curl_easy_init();

    if (curl) {
        string my_token = emailConfig.ibov_token;
        string url = "https://www.ibovfinancials.com/api/ibov/quotes/?symbol=" + symbol + "&token=" + my_token;



        //Definindo o CURLOPT_URL com a url
        //c.str() converte de string para const char*
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        //Definir callback, nesse caso, salvar dados na memoria (read)
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        //Definir local de armazenamento
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read);


        while (true) {

            read.clear();
            res = curl_easy_perform(curl);

            int http_code = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

            if (res == CURLE_OK && http_code == 200) {

                //Arquivos colocados em jsonData
                json jsonData = json::parse(read);

                double valor_atual = jsonData["data"][symbol]["last"];

                if (valor_atual >= LimiteParaVender) {

                    string mensagem = "O ativo " + symbol + " atingiu/ultrapassou o preco de venda (" + to_string(LimiteParaVender) + "). Cotacao atual: " + to_string(valor_atual);
                    string subject = "Alerta de venda: " + symbol;

                    //Tenta enviar o e-mail para venda
                    if (sendEmail(emailConfig, subject, mensagem) == true) cout << "Alerta de venda enviado!" << endl;
                    else cout << "Erro ao tentar enviar um alerta de venda!" << endl;

                }
                else if (valor_atual <= LimiteParaComprar) {

                    string mensagem = "O ativo " + symbol + " atingiu/caiu abaixo do preco de compra (" + to_string(LimiteParaComprar) + "). Cotacao atual: " + to_string(valor_atual);
                    string subject = "Alerta de compra: " + symbol;

                    //Tenta enviar o e-mail para compra
                    if (sendEmail(emailConfig, subject, mensagem) == true) cout << "Alerta de compra enviado!" << endl;
                    else cout << "Erro ao tentar enviar um alerta de compra!" << endl;

                }
            }
            else {
                cerr << "Erro na requisicao: " << curl_easy_strerror(res) << endl;
                cerr << "Codigo HTTP: " << http_code << endl;
            }

            this_thread::sleep_for(chrono::seconds(60));

        }
        curl_easy_cleanup(curl);
    }   

    curl_global_cleanup();
    return 0;
}