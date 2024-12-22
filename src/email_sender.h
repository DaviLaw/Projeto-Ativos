#ifndef EMAIL_SENDER_H
#define EMAIL_SENDER_H

#include <string>

// Estrutura auxiliar para upload do e-mail (callback)
struct UploadStatus {
    const char* read_ptr;
    size_t bytes_left;
};

// Estrutura para configurar o e-mail
struct EmailConfig {
    std::string smtp_server;
    std::string smtp_user;
    std::string smtp_pass;
    std::string email_to;
    std::string email_from;
    std::string ibov_token;
};


bool sendEmail(const EmailConfig& config, const std::string& subject, const std::string& body);

#endif // EMAIL_SENDER_H
#pragma once
