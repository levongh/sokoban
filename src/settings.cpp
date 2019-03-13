#include "settings.h"

Settings::Settings()
{
    load();
}

Settings::~Settings()
{
    save();
}

void Settings::load()
{
    //TODO
}

void Settings::save()
{
    //TODO
}

unsigned Settings::screenWidth() const
{
    static unsigned res {800};
    return res;
    //return m_scrrenWidth;
}

unsigned Settings::screenHeight() const
{
    static unsigned res{600};
    return res;
    //return m_scrrenHeight;
}

Settings& Settings::getInstance()
{
    static Settings instance;
    return instance;
}
