#ifndef CHANNEL_SETTINGS_HPP
# define CHANNEL_SETTINGS_HPP

# include "ft_irc.hpp"

class ChannelSettings
{

    public:
        ChannelSettings();
        ~ChannelSettings();

        void setTopic(const std::string& topic);
        void setChannelPassword(const std::string& password);
        void setInviteOnly(bool inviteOnly);
        void setTopicLocked(bool locked);

        const std::string& getTopic(void) const;
        const std::string& getChannelPassword(void) const;
        bool isInviteOnly(void) const;
        bool isTopicLocked(void) const;

    private:
        std::string _topic;
        std::string _channelPassword;
        bool        _inviteOnly;
        bool        _topicLocked;
};

# endif