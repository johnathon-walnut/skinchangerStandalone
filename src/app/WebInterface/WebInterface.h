#pragma once

// undefine any windows defines

#include "../../utils/httplib.hpp"

#include <string>
#include <vector>
#include <memory> // Include the <memory> header for smart pointers

class WebInterface
{
    std::string m_WebContent; // this will be loaded from the file system
    std::shared_ptr<httplib::Server> m_Server; // Use shared_ptr for httplib::Server
    std::unique_ptr<std::thread> m_ServerThread; // Use unique_ptr for std::thread

    using ColorText = std::pair<std::string, std::string>;

    std::vector<ColorText> m_Log;

public:
    inline void AddLog(const std::string& text, const std::string& color = "white")
	{
		m_Log.emplace_back(std::make_pair(text, color));
	}

    void Init();
    void Stop();
};

inline WebInterface g_WebInterface;
