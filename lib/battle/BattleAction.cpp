/*
 * BattleAction.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#include "StdInc.h"
#include "BattleAction.h"
#include "../CStack.h"

using namespace Battle;

BattleAction::BattleAction():
	side(-1),
	stackNumber(-1),
	actionType(INVALID),
	destinationTile(-1),
	additionalInfo(-1),
	selectedStack(-1)
{
}

BattleAction BattleAction::makeHeal(const CStack * healer, const CStack * healed)
{
	BattleAction ba;
	ba.side = healer->side;
	ba.actionType = STACK_HEAL;
	ba.stackNumber = healer->ID;
	ba.destinationTile = healed->getPosition();
	return ba;
}

BattleAction BattleAction::makeDefend(const CStack * stack)
{
	BattleAction ba;
	ba.side = stack->side;
	ba.actionType = DEFEND;
	ba.stackNumber = stack->ID;
	return ba;
}


BattleAction BattleAction::makeMeleeAttack(const CStack * stack, const CStack * attacked, BattleHex attackFrom)
{
	BattleAction ba;
	ba.side = stack->side;
	ba.actionType = WALK_AND_ATTACK;
	ba.stackNumber = stack->ID;
	ba.destinationTile = attackFrom;
	ba.additionalInfo = attacked->getPosition();
	return ba;

}
BattleAction BattleAction::makeWait(const CStack * stack)
{
	BattleAction ba;
	ba.side = stack->side;
	ba.actionType = WAIT;
	ba.stackNumber = stack->ID;
	return ba;
}

BattleAction BattleAction::makeShotAttack(const CStack * shooter, const CStack * target)
{
	BattleAction ba;
	ba.side = shooter->side;
	ba.actionType = SHOOT;
	ba.stackNumber = shooter->ID;
	ba.destinationTile = target->getPosition();
	return ba;
}

BattleAction BattleAction::makeMove(const CStack * stack, BattleHex dest)
{
	BattleAction ba;
	ba.side = stack->side;
	ba.actionType = WALK;
	ba.stackNumber = stack->ID;
	ba.destinationTile = dest;
	return ba;
}

BattleAction BattleAction::makeEndOFTacticPhase(ui8 side)
{
	BattleAction ba;
	ba.side = side;
	ba.actionType = END_TACTIC_PHASE;
	return ba;
}

std::string BattleAction::toString() const
{
	std::stringstream actionTypeStream;
	actionTypeStream << actionType;

	boost::format fmt("{BattleAction: side '%d', stackNumber '%d', actionType '%s', destinationTile '%s', additionalInfo '%d', selectedStack '%d'}");
	fmt % static_cast<int>(side) % stackNumber % actionTypeStream.str() % destinationTile % additionalInfo % selectedStack;
	return fmt.str();
}

std::ostream & operator<<(std::ostream & os, const BattleAction & ba)
{
	os << ba.toString();
	return os;
}
