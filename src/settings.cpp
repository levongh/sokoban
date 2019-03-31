#include <QDirIterator>

#include "../include/settings.h"

namespace  {

static const QString levelPath="levels/";

}

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
    m_availableLevels.clear();
    QDirIterator iter(levelsPath());
    while (iter.hasNext()) {
        iter.next();
        QFileInfo info(iter.fileInfo());
        if (info.completeSuffix() == "lvl") {
            m_availableLevels.push_back(std::make_pair<int, bool>(info.baseName().toInt(), true));
        }
    }
    std::sort(m_availableLevels.begin(), m_availableLevels.end(),
              [](const auto& lhs, const auto& rhs)->bool
    {
        return lhs.first < rhs.first;
    });
    //TODO do not allow gamer play all levels
}

void Settings::save()
{
    //TODO
}

QString Settings::levelsPath()const
{
    //TODO make it changable
    return levelPath;
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

const std::vector<std::pair<unsigned, bool> > Settings::getAvailableLevels() const
{
    return m_availableLevels;
}
