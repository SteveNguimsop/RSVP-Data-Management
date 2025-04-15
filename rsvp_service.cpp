// file: rsvp_service.cpp
#include "rsvp_service.h"

// Add or update RSVP status for a given player name
void RsvpService::addOrUpdateRsvp(const std::string& name, RsvpStatus status) {
    rsvpMap[name] = status;
}

// Add or update RSVP statuses for a batch of players
void RsvpService::addMultipleRsvps(const std::vector<RsvpEntry>& entries) {
    for (const auto& entry : entries) {
        addOrUpdateRsvp(entry.player.name, entry.status);
    }
}

// Retrieve list of player names who responded with "Yes"
std::vector<std::string> RsvpService::getConfirmedAttendees() const {
    std::vector<std::string> confirmed;
    for (const auto& entry : rsvpMap) {
        const std::string& name = entry.first;
        RsvpStatus status = entry.second;
        if (status == RsvpStatus::Yes) {
            confirmed.push_back(name);
        }
    }
    return confirmed;
}

// Count the number of responses in each RSVP category (Yes, No, Maybe)
std::map<RsvpStatus, int> RsvpService::getStatusCounts() const {
    std::map<RsvpStatus, int> counts = {
        { RsvpStatus::Yes, 0 },
        { RsvpStatus::No, 0 },
        { RsvpStatus::Maybe, 0 }
    };
    for (const auto& entry : rsvpMap) {
        const RsvpStatus status = entry.second;
        counts[status]++;
    }
    return counts;
}