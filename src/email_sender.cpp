#include "email_sender.h"
#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <cstring> 

// Callback de leitura para o upload
static size_t readCallback(void* ptr, size_t size, size_t nmemb, void* userp) {
    UploadStatus* upload_ctx = (UploadStatus*)userp;
    size_t max = size * nmemb;

    if (upload_ctx->bytes_left) {
        size_t to_copy = (upload_ctx->bytes_left < max) ? upload_ctx->bytes_left : max;
        memcpy(ptr, upload_ctx->read_ptr, to_copy);
        upload_ctx->read_ptr += to_copy;
        upload_ctx->bytes_left -= to_copy;
        return to_copy;
    }
    return 0; // Nada mais a enviar
}

static std::string formatEmail(const EmailConfig& config, const std::string& subject, const std::string& body) {
    std::stringstream ss;
    ss << "To: " << config.email_to << "\r\n"
        << "From: " << config.email_from << "\r\n"
        << "Subject: " << subject << "\r\n"
        << "\r\n"
        << body << "\r\n.\r\n";
    return ss.str();
}

bool sendEmail(const EmailConfig& config, const std::string& subject, const std::string& body) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "[sendEmail] Erro ao inicializar cURL.\n";
        return false;
    }

    struct curl_slist* recipients = nullptr;
    recipients = curl_slist_append(recipients, config.email_to.c_str());

    curl_easy_setopt(curl, CURLOPT_URL, config.smtp_server.c_str());
    curl_easy_setopt(curl, CURLOPT_USERNAME, config.smtp_user.c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, config.smtp_pass.c_str());

    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, config.email_from.c_str());
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

    std::string emailContent = formatEmail(config, subject, body);

    // Struct de controle para o callback
    UploadStatus upload_ctx;
    upload_ctx.read_ptr = emailContent.c_str();
    upload_ctx.bytes_left = emailContent.size();

    curl_easy_setopt(curl, CURLOPT_READFUNCTION, readCallback);
    curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
    curl_easy_setopt(curl, CURLOPT_INFILESIZE, (long)emailContent.size());

    // Ativa o modo de upload, 1L, pois retorna long
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

    // Usa SSL/TLS
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

    // Executa o envio
    CURLcode res = curl_easy_perform(curl);
    bool success = (res == CURLE_OK);

    if (!success) {
        std::cerr << "[sendEmail] Erro ao enviar e-mail: " << curl_easy_strerror(res) << std::endl;
    }

    // Limpa
    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);

    return success;
}
