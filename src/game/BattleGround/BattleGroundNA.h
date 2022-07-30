/*
 * This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef __BATTLEGROUNDNA_H
#define __BATTLEGROUNDNA_H

class BattleGround;

class BattleGroundNAScore : public BattleGroundScore
{
    public:
        BattleGroundNAScore() {};
        virtual ~BattleGroundNAScore() {};
        // TODO fix me
};

class BattleGroundNA : public BattleGround
{
        friend class BattleGroundMgr;

    public:
        BattleGroundNA();

        void Reset() override;

        /* inherited from BattlegroundClass */
        virtual void AddPlayer(Player* plr) override;
        virtual void StartingEventOpenDoors() override;

        void RemovePlayer(Player* plr, ObjectGuid guid) override;
        void HandleKillPlayer(Player* player, Player* killer) override;
        bool HandlePlayerUnderMap(Player* player) override;
};
#endif
