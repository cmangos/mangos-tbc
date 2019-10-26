/**
 *
 * @File : AnnounceMgr.cpp
 * @Authors : yukozh
 * @Date : 10/04/2019
 *
 **/

#include "AnnounceMgr.h"

uint32 current_announce = 0;
std::vector<std::string> m_announcements;

void AnnounceMgr::LoadFromDB()
{
    m_announcements.clear();
    current_announce = 0;
    QueryResult* result = WorldDatabase.PQuery(
        "SELECT `announce` "
        "FROM `pomelo_announce`; ");

    if (result)
	{
		do
		{
			Field* field = result->Fetch(); 
            m_announcements.push_back(field[0].GetCppString());
		} while (result->NextRow());
	}

    delete result;
}

std::string AnnounceMgr::NextAnnouncement()
{
    if (m_announcements.size() == 0)
        return "";
    ++current_announce;
    if (current_announce >= m_announcements.size())
        current_announce = 0;
    return m_announcements[current_announce];
}