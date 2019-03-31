#pragma once

#include <QString>
#include <vector>

class Settings
{
public:
    Settings(const Settings& other) = delete;
    Settings& operator= (const Settings& other) = delete;

public:
    void load();
    void save();

    QString levelsPath()const;
    unsigned screenWidth() const;
    unsigned screenHeight() const;
    const std::vector<std::pair<unsigned, bool> > getAvailableLevels() const;

public:
    static Settings& getInstance();

private:
    Settings();
    ~Settings();

private:
    unsigned m_scrrenWidth{0};
    unsigned m_scrrenHeight{0};

    std::vector<std::pair<unsigned, bool> > m_availableLevels;
};

