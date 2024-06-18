#include "ChannelSettings.hpp"

ChannelSettings::ChannelSettings() 
{
    this->_topic = "Default channel topic";
    this->_channelPassword = "";
    this->setTopicLocked(true);
    this->setInviteOnly(false);
}

ChannelSettings::~ChannelSettings() {}

void ChannelSettings::setTopic(const std::string& topic)
{
    this->_topic = topic;
}

void ChannelSettings::setChannelPassword(const std::string& password)
{
    this->_channelPassword = password;
}

void ChannelSettings::setInviteOnly(bool inviteOnly)
{
    this->_inviteOnly = inviteOnly;
}

void ChannelSettings::setTopicLocked(bool lock)
{
    this->_topicLocked = lock;
}

const std::string& ChannelSettings::getTopic(void) const
{
    return this->_topic;
}

const std::string& ChannelSettings::getChannelPassword(void) const
{
    return this->_channelPassword;
}

bool ChannelSettings::isInviteOnly(void) const
{
    return this->_inviteOnly;
}

bool ChannelSettings::isTopicLocked(void) const
{
    return this->_topicLocked;
}