#include "gameAction.hpp"
#include "odfaeg/Network/network.h"
using namespace odfaeg::core;
using namespace odfaeg::network;
namespace sorrok {
    void GameAction::operator()(const Hero::Novice&, Item& item, Hero* hero) {
        std::cout<<"action"<<std::endl;
        if (item.getType() == Item::HP_POTION) {
            float potionAmount = item.getAttributeVal(Item::POTION_AMOUNT);
            std::cout<<"hp potion amount : "<<potionAmount<<std::endl;
            if (hero->getLife() + potionAmount > hero->getMaxLife()) {
                hero->setLife(hero->getMaxLife());
            } else {
                hero->setLife(hero->getLife() + potionAmount);
            }
            SymEncPacket packet;
            std::string request = "ADDLIFE*"+conversionIntString(hero->getId())+"*"+conversionFloatString(potionAmount);
            packet<<request;
            Network::sendTcpPacket(packet);
        }
    }
    void GameAction::operator()(const Hero::Warrior&, Item& item, Hero* hero) {
    }
    void GameAction::operator()(const Hero::Magician&, Item& item, Hero* hero) {
    }
    void GameAction::operator()(const Hero::Thief&, Item& item, Hero* hero) {
    }
    void GameAction::operator()(const Hero::Novice&, Skill& skill, Hero* hero) {
    }
    void GameAction::operator()(const Hero::Warrior&, Skill& skill, Hero* hero) {
    }
    void GameAction::operator()(const Hero::Magician&, Skill& skill, Hero* hero) {
    }
    void GameAction::operator()(const Hero::Thief&, Skill& skill, Hero* hero) {
    }
}
