#include "WebInterface.h"

#include "../SkinChanger/SkinChanger.h"

#include <Windows.h>
#include "../../../resource.h"
#include <format>
#include "../../utils/json.hpp"

HMODULE GCM()
{
	return g_App.GetHandle();
}

std::string GetIndexResource()
{
	std::string result;

	HRSRC hRes = FindResourceW(GCM(), MAKEINTRESOURCEW(INDEX_PAGE), MAKEINTRESOURCEW(TEXTFILE));
	HGLOBAL hData = LoadResource(GCM(), hRes);
	DWORD dwSize = SizeofResource(GCM(), hRes);
	char* hFinal = (char*)LockResource(hData);
	result.assign(hFinal, dwSize);

	FreeResource(hData);

	return result;
}

void WebInterface::Init()
{
	if (!m_Server)
		m_Server = std::make_shared<httplib::Server>();

	m_WebContent = GetIndexResource();

	m_Server->Get("/", [&](const httplib::Request& req, httplib::Response& res)
				  {
					  res.set_content(m_WebContent, "text/html");
				  });

	// I honestly kinda messed up with these, it should pass the attribute index instead of a string, fnv1a is only here because of that

	m_Server->Get("/remove", [&](const httplib::Request& req, httplib::Response& res)
				  {
					  std::string strIndex = req.get_param_value("index");
					  std::string strAttribute = req.get_param_value("attribute");

					  if (strIndex.empty() || strAttribute.empty())
					  {
						  res.set_content("Invalid request", "text/plain");
						  return;
					  }

					  int index = std::stoi(strIndex);

					  g_SkinChanger.WebRemoveAttribute(index, strAttribute);
				  });

	m_Server->Get("/update", [&](const httplib::Request& req, httplib::Response& res)
				  {
					  std::string strIndex = req.get_param_value("index");
					  std::string strAttribute = req.get_param_value("attribute");
					  std::string strValue = req.get_param_value("value");

					  if (strIndex.empty() || strAttribute.empty() || strValue.empty())
					  {
						  res.set_content("Invalid request", "text/plain");
						  return;
					  }

					  int index = std::stoi(strIndex);
					  float value = std::stof(strValue);

					  g_SkinChanger.WebSetAttribute(index, strAttribute, value);
				  });

	m_Server->Get("/save", [&](const httplib::Request& req, httplib::Response& res)
				  {
					  g_SkinChanger.Save();
					  res.set_content("{}", "text/plain");
				  });

	m_Server->Get("/load", [&](const httplib::Request& req, httplib::Response& res)
				  {
					  g_SkinChanger.Load();
					  res.set_content("{}", "text/plain");
				  });

	m_Server->Get("/weaponIndex", [&](const httplib::Request& req, httplib::Response& res)
				  {
					  res.set_content(std::format("{}", g_SkinChanger.m_nCurrentWeaponIndex), "text/plain");
				  });

	m_Server->Get("/getForIndex", [&](const httplib::Request& req, httplib::Response& res)
				  {
					  std::string strIndex = req.get_param_value("index");
					  auto intIndex = std::stoi(strIndex);

					  const auto& weaponAttributes = g_SkinChanger.GetSkinInfo(intIndex);

					  if (weaponAttributes.m_Attributes.size() == 0)
					  {
						  res.set_content("{}", "application/json");
						  return;
					  }

					  nlohmann::json json;
					  for (auto& attribute : weaponAttributes.m_Attributes)
					  {
						  float val = attribute.attributeValue;

						  if (attribute.attributeIndex == attributes::paintkit_proto_def_index)
						  {
							  val = static_cast<float>(StupidFloatToInt(val));
						  }

						  json[std::format("{}", static_cast<int>(attribute.attributeIndex))] = val;
					  }

					  res.set_content(json.dump(), "application/json");
				  });

	if (!m_ServerThread)
	{
		m_ServerThread = std::make_unique<std::thread>([this]()
													   {
														   m_Server->listen("localhost", 4077);
													   });

		m_ServerThread->detach();
	}

	Beep(500, 100);
}

void WebInterface::Stop()
{
	if (m_Server)
		m_Server->stop();

	Beep(750, 50);
}
