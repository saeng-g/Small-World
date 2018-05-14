//
//  Player.cpp
//  SMALL WORLD
//
//  Created by Kyungjin Kim on 2018-02-07.
//  Copyright © 2018 Ky Kim. All rights reserved.
//

#include <iostream>
#include "Player.h"

int Player::ID_generator = 0;

//constructor & destructor
Player::Player() {
    ID_generator++;
    ID = ID_generator;
    coins = 0;
    active = nullptr;
    passive = nullptr;
    passive_spirit = nullptr;
    num_conq = 0;
}

Player::~Player() {}

//Accessors and Modifiers
int Player::getID() { return ID; }

int Player::getAlly() { return ally; }
void Player::setAlly(int id) { this->ally = id; }

Combo* Player::getActive() { return active; }
void Player::setActive(Combo* combo) { active = combo; }
Combo* Player::getPassive() { return passive; }
void Player::setPassive(Combo* combo) { passive = combo; }
Combo* Player::getPassiveSpirit() { return passive_spirit; }
void Player::setPassiveSpirit(Combo* combo) { passive_spirit = combo; }

int Player::getCoins() { return coins; }
void Player::setCoins(int coins) { this->coins = coins; }

std::vector<Region*> Player::getActiveReg() { return active_regions; }
std::vector<Region*> Player::getPassiveReg() { return passive_regions; }
std::vector<Region*> Player::getSpiritReg() { return spirit_regions; }

void Player::decline(Deck* deck) {
    
    //get rid of the old passive if applicable
    if (passive != nullptr) {
        deck->restock(passive);
        passive = nullptr;
    }
    
    //assign to passive_spirit if power is spirit
    if (active->getPower()->getType() == Power::SPIRIT) {
        setPassiveSpirit(active);
        active = nullptr;
    }
    
    //asign to passive if not spirit and discard the power component
    else {
        setPassive(active);
        active = nullptr;
        deck->restock(passive->getPower());
        passive->setPowerNull();
    }
    notify();
}

/* inputs race indicator and deck object;
directs the race combo to the Player's attributes */

void Player::picks_race(int position, Deck* deck) {
    for (int i = 1; i <= 6; i++) {
        if (i == position) {
            deck->comboColumn.at(i - 1)->setInColumn(false);
            deck->comboColumn.at(i - 1)->setInPlay(true);
            deck->comboColumn.at(i - 1)->setActive(true);
            coins += (deck->comboColumn.at(i - 1)->getCoins());
            active = deck->comboColumn.at(i - 1);
            
            deck->remove(i - 1);
            deck->refill();
            
            break;
            }
        else {
            deck->comboColumn.at(i - 1)->placeCoins();
            coins--;
        }
    }
    notify();
}

/*
 
 conquering:
 
 */

int Player::conquers(Combo* combo, Region* to, int req_tok) {
    
    /*
     check if it has owner or tokens (lost tribe)
     This is to keep track of how many regions conquered were non-empty
     stores info in num_conq
     useful for scoring for orcs (race) and pillaging (power) in scoring phase
     */
    
    bool owned = true;
    bool tokens = true;
    if (to->getTokens() <= 0) {
        tokens = false;
    }
    if (to->getOwner() == nullptr) {
        owned = false;
    }
    
    //Owned
    if (owned) {
        
        /*
         remove from ex-owner's list of regions
         1) identify whether to look in activeReg, passiveReg, or SpiritReg
         2) find the region in the Reg vector and erase it
         */
        
        //Part 1
        int indic = getOccupantIndic(to);
        int size = getOccupantSize(indic, to);
        
        //Part 2
        eraseOwner(indic, size, to);
        
        //change to new owner
        newOwner(combo, req_tok, to);
        num_conq++;
    }
    
    //Not Owned but tokens
    else if (tokens){
        //change to new owner
        newOwner(combo, req_tok, to);
        num_conq++;
    }
    
    //Not Owned and no tokens
    else {
        //change to new owner
        newOwner(combo, req_tok, to);
    }
    
    return 0; //indicates dice has not been rolled; may continue conquest
}

int Player::getOccupantIndic(Region* to) {
    int indic = 0; // active = 1; passive = 2; spirit = 3;
    if (to->getOccupant() == to->getOwner()->active) {
        indic = 1;
    }
    else if (to->getOccupant() == to->getOwner()->passive) {
        indic = 2;
    }
    else if (to->getOccupant() == to->getOwner()->passive_spirit) {
        indic = 3;
    }
    else {
        //error
        std::cout << "error @ conquers: OccupantIndic" << std::endl;
        indic = -1;
    }
    return indic;
}

int Player::getOccupantSize(int indic, Region* to) {
    int size = 0;
    if (indic == 1)
        size = (int)( to->getOwner()->getActiveReg().size() );
    else if (indic == 2)
        size = (int)( to->getOwner()->getPassiveReg().size() );
    else if (indic == 3)
        size = (int)( to->getOwner()->getSpiritReg().size() );
    else
        //error
        std::cout << "error @ conquers: OccupantSize" << std::endl;
        size = -1;
    return size;
}

void Player::eraseOwner(int indic, int size, Region* to) {
    int redeployable = to->getTokens();
    
    // if Occupant is Owner's active
    if (indic == 1) {
        //clean up tokens
        Combo* tempCombo = to->getOwner()->getActive();
        eraseOwnerTokens(tempCombo, redeployable);
        tempCombo = nullptr;
        
        //remove the region from the list of owned regions by combo
        std::vector<Region*> tempList = to->getOwner()->getActiveReg();
        for (int i = 0; i < size; i++) {
            if (to->getOwner()->getActiveReg()[i] == to) {
                tempList.erase(tempList.begin() + i - 1);
                to->getOwner()->getActiveReg() = tempList;
                break;
            }
        }
    }
    
    //if Occupant is Owner's passive
    else if (indic == 2) {
        //clean up tokens
        Combo* tempCombo = to->getOwner()->getPassive();
        eraseOwnerTokens(tempCombo, redeployable);
        tempCombo = nullptr;
        
        //remove the region from the list of owned regions by combo
        std::vector<Region*> temp = to->getOwner()->getPassiveReg();
        for (int i = 0; i < size; i++) {
            if (to->getOwner()->getPassiveReg()[i] == to) {
                temp.erase(temp.begin() + i - 1);
                to->getOwner()->getPassiveReg() = temp;
                break;
            }
        }
    }
    
    //if Occupant is Owner's spirit passive
    else if (indic == 3) {
        //clean up tokens
        Combo* tempCombo = to->getOwner()->getPassiveSpirit();
        eraseOwnerTokens(tempCombo, redeployable);
        tempCombo = nullptr;
        
        //remove the region from the list of owned regions by combo
        std::vector<Region*> temp = to->getOwner()->getSpiritReg();
        for (int i = 0; i < size; i++) {
            if (to->getOwner()->getSpiritReg()[i] == to) {
                temp.erase(temp.begin() + i - 1);
                to->getOwner()->getSpiritReg() = temp;
                temp.~vector();
            }
        }
    }
    else {
        //error
        std::cout << "error @ conquers: eraseOwner (invalid indic)" << std::endl;
    }
}

/*
 
 eraseOwnerTokens:
 change token settings of the occupant combo that is being conquered:
 - decrease defensive toks by the # of toks removed from region (indicated by redeployable)
 - "discard" one of the tokens that was occupying the region (unless Race == ELVES)
    - decrease total # of toks
    - decrease # of tokens to be given back as redeployable
 - give back the redeployable tokens to the combo to be used by the combo holder
 
 */

void Player::eraseOwnerTokens(Combo* combo, int redeployable) {
    if (combo->getRace()->getType() != Race::ELVES) {
        combo->setDefensiveTok(combo->getDefensiveTok() - redeployable);
        
        redeployable--;
        combo->removeOneTotalToken();
        
        combo->setRedeployable(redeployable);
    }
    else {
        combo->setDefensiveTok(combo->getDefensiveTok() - redeployable);
        combo->setRedeployable(redeployable);
    }
}

void Player::newOwner(Combo* combo, int conq_tok, Region* to) {
    to->setOwner(this);
    to->setOccupant(combo);
    to->setTokens(conq_tok);
    active_regions.push_back(to); //add to owner's list
    
    combo->setOffensiveTok(combo->getOffensiveTok() - conq_tok);
    combo->setDefensiveTok(combo->getDefensiveTok() + conq_tok);
}

//Conquerable checks: conquerable_Type(), conquerable_Cond(), conquerable_Tok()

bool Player::conquerable_Type(Combo* combo, Region* to) {
    bool check = false;     //return bool
    
    //check if the region is a body of water & if the combo power is SEAFARING
    //ONLY seafarers can conquer body of water
    bool waterCheck = true;
    if (to->getType() == Region::SEA || to->getType() == Region::LAKE)
        if ( !(combo->getPower()->getType() == Power::SEAFARING) )
            waterCheck = false;
    
    check = waterCheck;
    return check;
}

bool Player::conquerable_Cond(Combo* combo, Region* to) {
    bool check = false;     //return bool
    
    //if no owner, return true;
    if (to->getOwner() == nullptr) {
        return true;
    }
    
    //check if the owner of the region is your ally (against Diplomat)
    //CANNOT conquer region of an ally
    //However, ghouls
    bool checkAlly = true;
    if (to->getOwner()->getID() == ally) {
        if (combo->getRace()->getType() != Race::GHOULS)
            checkAlly = false;
        else if (combo->getPower() != nullptr)
            checkAlly = false;
    }
    
    //check if the region has a dragon or hero
    //CANNOT conquer dragon or hero
    bool checkDH = true;
    if (to->getDragon() || to->getHero())
        checkDH = false;
    
    //check if the region has a hole-in-the-ground
    bool checkHole = true;
    if (to->getHole())
        checkHole = false;
    
    check = checkAlly && checkDH && checkHole;
    return check;
}

int Player::conquerable_Tok(Combo* combo, Region* to) {
    /*
     
     NOTE:
     
     "To conquer a Region, a player must have available to deploy:
        2 Race tokens + 1 additional Race token for each Encampment,
        Fortress, Mountain, or Troll's Lair marker + 1 additional Race token
        for each Lost Tribe or other player's Race token already present in
        the Region. " - SmallWorld rulebook
     
     */
    int cost = 2;
    cost = cost + to->getTokens() + to->getMountain() + to->getNumEncampment() + to->getTrollsLair() + to->getFortress();
    
    //calculating the advantages of the race & power specials
    int advantage = 0;
    
    //racial advantages
    int race = combo->getRace()->getType(); //for easy ref
    if (race == Race::GIANTS) {
        if (to->getBesideMt())
            advantage++;
    }
    else if (race == Race::TRITONS) {
        if (to->getCoastal())
            advantage++;
    }
    
    //power advantages
    int power = 0;
    if (combo->getPower() != nullptr) {            //check if combo is passive: power == nullptr
        power = combo->getPower()->getType();
    }
    if (power == Power::COMMANDO) {
        advantage++;
    }
    else if (power == Power::MOUNTED) {
        if (to->getType() == Region::FARMLAND || to->getType() == Region::HILL)
            advantage++;
    }
    
    //calculate required token
    int req_tok = cost - advantage;
    if (req_tok < 1) {
        req_tok = 1;
    }
    return req_tok;
}

/*
 
 methods for redeployment:
 - collectTokens(int indic): collect tokens for redeployment from all occupied region of the combo.
 - redeploy(int indic, int num_Token, Region* region): places redeployable tokens.
 
 */

void Player::collectTokens(int indic) {
    //indic: active = 1, passive = 2
    //NOTE: if race is amazon, take 4 of the tokens and place it as an offensive token as 4 tokens cannot be used for defense
    int num_tokens = 0;
    if (indic == 1) {
        for (int i = 0; i < active_regions.size(); i++) {
            num_tokens += active_regions[i]->getTokens() - 1;
            active_regions[i]->setTokens(1);
        }
        
        active->setDefensiveTok(active->getDefensiveTok() - num_tokens);
        
        if (active->getRace()->getType() == Race::AMAZONS) {
            int offensive_remainder = active->getOffensiveTok();        //number of offensive tokens remaining post conquest
            int needed = 4 - offensive_remainder;                       //number of offensive tokens needed to fill 4
            num_tokens -= needed;                                       //subtract amount needed from retracted tokens
            active->setOffensiveTok(4);                                 //set Number of offensive tokens to 4
        }
        
        else {
            num_tokens += active->getOffensiveTok();                    //add number of offensive tokens remaining to retracted tokens
            active->setOffensiveTok(0);                                 //offensive tokens are all converted to redeployable
        }
        
        int redeployable = active->getRedeployable(); //should be zero but just in case of incomplete redeployment / conversion in last turn(s)
        active->setRedeployable(redeployable + num_tokens);
    }
    else if (indic == 2) {
        for (int i = 0; i < passive_regions.size(); i++) {
            num_tokens += passive_regions[i]->getTokens() - 1;
            passive_regions[i]->setTokens(1);
        }
        
        if (passive->getRace()->getType() == Race::AMAZONS) {
            int offensive_remainder = passive->getOffensiveTok();        //number of offensive tokens remaining post conquest
            int needed = 4 - offensive_remainder;                       //number of offensive tokens needed to fill 4
            num_tokens -= needed;                                       //subtract amount needed from retracted tokens
            passive->setOffensiveTok(4);                                 //set Number of offensive tokens to 4
        }
        
        else {
            num_tokens += active->getOffensiveTok();                    //add number of offensive tokens remaining to retracted tokens
            active->setOffensiveTok(0);                                 //offensive tokens are all converted to redeployable
        }
        
        int redeployable = passive->getRedeployable(); //should be zero but just in case of incomplete redeployment / conversion in last turn(s)
        passive->setRedeployable(redeployable + num_tokens);
    }
    else {
        //error
        std::cout << "error@ collectTokens invalid indic" << std::endl;
    }
}

void Player::readyConquest(int indic) {
    if (indic == 1) {
        collectTokens(1);
        active->setOffensiveTok(active->getRedeployable());
    }
    else if (indic == 2) {
        collectTokens(2);
        passive->setOffensiveTok(passive->getRedeployable());
    }
}

void Player::redeploy(Combo* combo, int num_tokens, Region* to) {
    //NOTE: assumes that redepCheck is performed prior to method call
    
    //reduce redeployable
    int redeployable = combo->getRedeployable();
    redeployable -= num_tokens;
    combo->setRedeployable(redeployable);
    
    //place num_tokens to to Region
    int preexisting = to->getTokens();
    num_tokens += preexisting;
    to->setTokens(num_tokens);
}

bool Player::redepCheck(int indic, int num_tokens, Region* to) {
    bool check = false;
    
    //if active race
    if (indic == 1) {
        //check1: check that the region is a valid region (conquered by the race)
        bool regionCheck = false;
        for (int i = 0; i < active_regions.size(); i++) {
            if (active_regions[i] == to) {
                regionCheck = true;
                break;
            }
        }
        
        //check2: check that the num_tokens being placed is valid (that there are enough redeployable tokens)
        bool numCheck = false;
        int redeployable = active->getRedeployable();
        redeployable -= num_tokens;
        if (redeployable >= 0) {
            numCheck = true;
        }
        
        check = regionCheck && numCheck;
    }
    
    //if race in decline
    else if (indic == 2) {
        //check1: check that the region is a valid region (conquered by the race)
        bool regionCheck = false;
        for (int i = 0; i < passive_regions.size(); i++) {
            if (passive_regions[i] == to) {
                regionCheck = true;
                break;
            }
        }
        
        //check2: check that the num_tokens being placed is valid (that there are enough redeployable tokens)
        bool numCheck = false;
        int redeployable = passive->getRedeployable();
        redeployable -= num_tokens;
        if (redeployable >= 0) {
            numCheck = true;
        }
        
        check = regionCheck && numCheck;
    }
    else {
        //error
        std::cout << "error@ redepCheck : invalid indic" << std::endl;
    }
    
    return check;
}

/*
 
 scoring methods:
 - scores(): main method of calculating scores
 - active_score(): calculates the score obtained by the active race
 - passive_score(): calculates the score obtained by the in-decline race
 - spirit_score(): calculates the score obtained by the in-decline spirit race
 - race_score(): calculates the score advantages of a race given a particular region
 - power_score(): calculates the score advantages of a power given a particular region
 
 NOTE: that race_score() and power_score() can only handle region specific benefits (ie, SWAMP bonus or Mine bonus)
 other bonuses (ie ALCHEMIST bonus / MERCHANT bonus) must be handled separately.
 
 */

int Player::scores() {
    
    //setting up counter size
    int active_sz = (int) active_regions.size();
    int passive_sz = (int) passive_regions.size();
    int spirit_sz = (int) spirit_regions.size();
    
    int active = 0;
    int passive = 0;
    int spirit = 0;
    
    //player should always have an active but may not have a race in decline or a spirit in decline
    active = active_score(active_sz);
    if (this->passive != nullptr)
        passive = passive_score(passive_sz);
    if (this->passive_spirit != nullptr)
        spirit = spirit_score(spirit_sz);
    
    int total = active + passive + spirit;
    
    this->coins += total;
    notify();
    return total; //returns points earned by the player this turn
    
}

int Player::active_score(int active_sz) {
    int race = active->getRace()->getType();
    int power = active->getPower()->getType();
    
    //scoreboard
    int rScore = 0;
    int pScore = 0;
    int occupancy_score = 0;
    int conquer_score = 0;
    int water_score = 0;
    
    for (int i = 0; i < active_sz; i++) {
        rScore += race_score(true, race, active_regions[i]);
        pScore += power_score(power, active_regions[i]);
        int region_type = active_regions[i]->getType();
        if (region_type == Region::SEA || region_type == Region::LAKE) {
            //occupying body of water rewards 3 points per turn.
            //(one will be counted in occupancy, the other two needs to be accounted for separately)
            water_score += 2;
        }
    }
    
    if (power == Power::ALCHEMIST)
        pScore += 2;
    
    occupancy_score = active_sz;
    
    if (power == Power::MERCHANT)
        occupancy_score *= 2;
    
    if (race == Race::ORCS)
        conquer_score += num_conq;
    if (power == Power::PILLAGING)
        conquer_score += num_conq;
    
    int active_score = rScore + pScore + occupancy_score + conquer_score + water_score;
    return active_score;
}

int Player::passive_score(int passive_sz) {
    int race = active->getRace()->getType();
    
    //scoreboard
    //note: no conquer score since only race able to conquer in decline are ghouls (they do not get conquer score)
    //note: no power score (pScore) since passive race does not have powers (unless spirit - handled via spirit_score())
    
    int rScore = 0;
    int occupancy_score = 0;
    int water_score = 0;
    
    for (int i = 0; i < passive_sz; i++) {
        rScore += race_score(false, race, passive_regions[i]);
        int region_type = passive_regions[i]->getType();
        if (region_type == Region::SEA || region_type == Region::LAKE) {
            //occupying body of water rewards 3 points per turn.
            //(one will be counted in occupancy, the other two needs to be accounted for separately)
            water_score += 2;
        }
    }
    
    occupancy_score = passive_sz;
    
    int passive_score = rScore + occupancy_score + water_score;
    return passive_score;
}

int Player::spirit_score(int spirit_sz) {
    int race = passive_spirit->getRace()->getType();
    
    //scoreboard
    //note: no conquer score since only race able to conquer in decline are ghouls (they do not get conquer score)
    //note: no power score (pScore) since passive race does not have powers (unless spirit - handled via spirit_score())
    //note: no water score since spirit cannot have been seafarers (they are both POWER)
    
    int rScore = 0;
    int occupancy_score = 0;
    
    for (int i = 0; i < spirit_sz; i++) {
        rScore += race_score(false, race, spirit_regions[i]);
    }
    
    occupancy_score = spirit_sz;
    
    int spirit_score = rScore + occupancy_score;
    return spirit_score;
}

int Player::race_score(bool active, int race, Region* region) {
    int race_score = 0;
    if (race == Race::HUMANS && region->getType() == Region::FARMLAND && active)
        race_score++;
    else if (race == Race::WIZARDS && region->getMagic() && active)
        race_score++;
    //Dwarves get extra points regardless of whether or not it is in decline
    else if (race == Race::DWARVES && region->getMine())
        race_score++;
    return race_score;
}

int Player::power_score(int power, Region* region) {
    int power_score = 0;
    if (power == Power::FOREST && region->getType() == Region::FOREST)
        power_score++;
    else if (power == Power::SWAMP && region->getType() == Region::SWAMP)
        power_score++;
    else if (power == Power::HILL && region->getType() == Region::HILL)
        power_score++;
    else if (power == Power::FORTIFIED && region->getFortress())
        power_score++;
    return power_score;
}


//printing methods:
void Player::printInfo() {
    std::string active_str = "";
    std::string passive_str = "";
    std::string spirit_str = "";
    if (active != nullptr)
        active_str = active->getString();
    if (passive != nullptr)
        passive_str = passive->getString();
    if (passive_spirit != nullptr)
        spirit_str = passive_spirit->getString();
        
        
    std::cout << "Info: Player " << ID << ":\n"
    << "\tActive Race: " << active_str << "\n"
    << "\tPassive Race: " << passive_str << "\n"
    << "\tPassive Spirit: " << spirit_str << "\n"
    << std::endl;
}

void Player::printActiveReg() {
    std::cout << "Regions occupied by the active race for player " << ID << ": ";
    for (int i = 0; i < active_regions.size(); i++) {
        std::cout << active_regions[i]->getID() << " " << std::endl;
    }
}

void Player::printPassiveReg() {
    std::cout << "Regions occupied by the race in decline for player " << ID << ": ";
    for (int i = 0; i < passive_regions.size(); i++) {
        std::cout << passive_regions[i]->getID() << " " << std::endl;
    }
}

//inherited Subject
void Player::attach(Observer* o) { this->Subject::attach(o); }
void Player::detach(Observer* o) { this->Subject::detach(o); }
void Player::notify() { this->Subject::notify(); }
