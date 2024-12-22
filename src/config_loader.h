#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include <string>
#include "email_sender.h" 

EmailConfig loadEmailConfig(const std::string& filename);

#endif // CONFIG_LOADER_H
#pragma once
