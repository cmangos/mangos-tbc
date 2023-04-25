
struct npc_target_dummyAI : public Scripted_NoMovementAI
{
	npc_target_dummyAI(Creature* creature) : Scripted_NoMovementAI(creature) { Reset(); }

	std::unordered_map<ObjectGuid, time_t> attackers;
	std::map<ObjectGuid, uint64> m_damageMap;

	time_t m_combatStartTime;
	time_t m_combatEndTime;

	uint32 m_uiCombatTimer;

	void Reset() override
	{
		attackers.clear();

		m_uiCombatTimer = 2000;
		SetCombatMovement(false);
		SetReactState(REACT_PASSIVE);
	}

	void Aggro(Unit* who) override
	{
		m_damageMap.clear();
		m_combatStartTime = time(nullptr);
		m_combatEndTime = 0;
	}

	void AddAttackerToList(Unit* pWho)
	{
		auto itr = attackers.find(pWho->GetObjectGuid());
		if (itr != attackers.end())
			itr->second = std::time(nullptr);
		else
			attackers.emplace(pWho->GetObjectGuid(), std::time(nullptr));
	}

	void EnterEvadeMode() override
	{
		m_combatEndTime = time(nullptr);
		m_uiCombatTimer = 0;
		ScriptedAI::EnterEvadeMode();
	}

	void SpellHit(Unit* caster, const SpellEntry* spellInfo) override
	{
		if (caster)
			AddAttackerToList(caster);
	}

	void DamageTaken(Unit* dealer, uint32& uiDamage, DamageEffectType damagetype, SpellEntry const* spellInfo) override
	{
		if (dealer)
		{
			m_damageMap[dealer->GetObjectGuid()] += uiDamage;
			AddAttackerToList(dealer);
		}
	}

	void ReceiveEmote(Player* player, uint32 uiEmote) override
	{
		if (uiEmote == TEXTEMOTE_WAVE)
		{
			time_t seconds = (m_combatEndTime ? m_combatEndTime : time(nullptr)) - m_combatStartTime;
			ChatHandler(player).PSendSysMessage("Player DPS during last combat that lasted %ld seconds: %ld Total Damage: %lu", seconds, m_damageMap[player->GetObjectGuid()] / seconds, m_damageMap[player->GetObjectGuid()]);
		}
	}

	void UpdateAI(const uint32 uiDiff) override
	{
		if (m_creature->IsInCombat())
		{
			if (m_uiCombatTimer <= uiDiff)
			{
				for (auto itr = attackers.begin(); itr != attackers.end();)
				{
					Unit* pAttacker = m_creature->GetMap()->GetUnit(itr->first);

					if (!pAttacker || !pAttacker->IsInWorld())
					{
						itr = attackers.erase(itr);
						continue;
					}
					if (itr->second + 5 < std::time(nullptr))
					{
						m_creature->_removeAttacker(pAttacker);
						m_creature->getThreatManager().modifyThreatPercent(pAttacker, -101.0f);
						itr = attackers.erase(itr);
						continue;
					}
					++itr;
				}

				if (m_creature->getThreatManager().isThreatListEmpty())
					EnterEvadeMode();

				m_uiCombatTimer = 2000;
			}
			else
				m_uiCombatTimer -= uiDiff;
		}
	}
};

UnitAI* GetAI_npc_target_dummy(Creature* creature)
{
	return new npc_target_dummyAI(creature);
}

void AddSC_TargetDummy()
{
	Script* pNewScript = new Script;
	pNewScript = new Script;
	pNewScript->Name = "npc_target_dummy";
	pNewScript->GetAI = &GetAI_npc_target_dummy;
	pNewScript->RegisterSelf();
}