#include "angband.h"

void _blood_flow_spell(int cmd, variant *res)
{
    switch (cmd)
    {
    case SPELL_NAME:
        var_set_string(res, "Blood Flow");
        break;
    case SPELL_DESC:
        var_set_string(res, "Cuts yourself.");
        break;
    case SPELL_SPOIL_DESC:
        var_set_string(res, "Gives player Light Cut (10) status, or increases current cut status by 20%, whichever is greater.");
        break;
    case SPELL_CAST:
    {
        int cut = p_ptr->cut;
        cut += cut/5;
        if (cut < CUT_LIGHT)
            cut = CUT_LIGHT;

        set_cut(cut, FALSE);
        var_set_bool(res, TRUE);
        break;
    }
    default:
        default_spell(cmd, res);
        break;
    }
}

void _blood_sight_spell(int cmd, variant *res)
{
    switch (cmd)
    {
    case SPELL_NAME:
        var_set_string(res, "Blood Sight");
        break;
    case SPELL_DESC:
        var_set_string(res, "Detects living creatures in the vicinity.");
        break;
    case SPELL_SPOIL_DESC:
        var_set_string(res, "Detects living creatures in the vicinity. At L30, gives temporary ESP Living for 30+d30 rounds.");
        break;
    case SPELL_CAST:
    {
        if (p_ptr->lev < 30)
            detect_monsters_living(DETECT_RAD_DEFAULT, "You sense potential blood!");
        else
            set_tim_blood_sight(randint1(30) + 30, FALSE);
        var_set_bool(res, TRUE);
        break;
    }
    default:
        default_spell(cmd, res);
        break;
    }
}

void _blood_spray_spell(int cmd, variant *res)
{
    switch (cmd)
    {
    case SPELL_NAME:
        var_set_string(res, "Blood Spray");
        break;
    case SPELL_DESC:
        var_set_string(res, "Cuts yourself, splattering nearby enemies.");
        break;
    case SPELL_SPOIL_DESC:
        var_set_string(res, "Generates a radius 3 blood ball centered on the player for 2*(3d5+L+L/5) damage. Radius is increased to 4 at L30.");
        break;
    case SPELL_INFO:
        var_set_string(res, info_damage(3, 5, p_ptr->lev + p_ptr->lev/4));
        break;
    case SPELL_CAST:
    {
        int dice = 3;
        int sides = 5;
        int rad = (p_ptr->lev < 30) ? 3 : 4;
        int base = p_ptr->lev + p_ptr->lev/4;

        fire_ball(GF_BLOOD, 5, 2*(damroll(dice, sides) + base), rad);
        var_set_bool(res, TRUE);
        break;
    }
    default:
        default_spell(cmd, res);
        break;
    }
}

void _blood_bath_spell(int cmd, variant *res)
{
    switch (cmd)
    {
    case SPELL_NAME:
        var_set_string(res, "Blood Bath");
        break;
    case SPELL_DESC:
        var_set_string(res, "Restores constitution and cures poison.");
        break;
    case SPELL_CAST:
    {
        bool chg = FALSE;
        if (do_res_stat(A_CON)) chg = TRUE;
        if (set_poisoned(0, TRUE)) chg = TRUE;
        if (!chg) msg_print("You don't need a bath just yet.");
        var_set_bool(res, TRUE);
        break;
    }
    default:
        default_spell(cmd, res);
        break;
    }
}

void _blood_shield_spell(int cmd, variant *res)
{
    switch (cmd)
    {
    case SPELL_NAME:
        var_set_string(res, "Blood Shield");
        break;
    case SPELL_DESC:
        var_set_string(res, "Gives bonus to AC depending on how wounded you are.  Grants reflection if you are really hurting.");
        break;

    case SPELL_SPOIL_DESC:
        var_set_string(res, "Player gains 100*(MHP-CHP)/MHP to AC. If more than 60% wounded, player also gains reflection.");
        break;
    case SPELL_CAST:
    {
        set_tim_blood_shield(randint1(20) + 30, FALSE);
        var_set_bool(res, TRUE);
        break;
    }
    default:
        default_spell(cmd, res);
        break;
    }
}

void _blood_seeking_spell(int cmd, variant *res)
{
    switch (cmd)
    {
    case SPELL_NAME:
        var_set_string(res, "Blood Seeking");
        break;
    case SPELL_DESC:
        var_set_string(res, "Gives slay living to your weapon.");
        break;
    case SPELL_SPOIL_DESC:
        var_set_string(res, "For 30+d30 rounds, the player's weapon will Slay Living (x2).");
        break;
    case SPELL_CAST:
    {
        set_tim_blood_seek(randint1(30) + 30, FALSE);
        var_set_bool(res, TRUE);
        break;
    }
    default:
        default_spell(cmd, res);
        break;
    }
}

void _blood_rage_spell(int cmd, variant *res)
{
    switch (cmd)
    {
    case SPELL_NAME:
        var_set_string(res, "Blood Rage");
        break;
    case SPELL_DESC:
        var_set_string(res, "Enter a blood frenzy.  Gives speed and big bonuses to hit and damage.");
        break;
    case SPELL_SPOIL_DESC:
        var_set_string(res, "For L/2+d(L/2) rounds, player is hasted and berserk.");
        break;
    case SPELL_CAST:
    {
        int dur = randint1(p_ptr->lev/2) + p_ptr->lev/2;
        set_fast(dur, FALSE);
        set_shero(dur, FALSE);
        var_set_bool(res, TRUE);
        break;
    }
    default:
        default_spell(cmd, res);
        break;
    }
}

void _blood_feast_spell(int cmd, variant *res)
{
    switch (cmd)
    {
    case SPELL_NAME:
        var_set_string(res, "Blood Feast");
        break;
    case SPELL_DESC:
        var_set_string(res, "You begin to feast on your opponents blood, doing extra damage but at a cost to your own health.");
        break;
    case SPELL_SPOIL_DESC:
        var_set_string(res, "For 25+d25 rounds, each melee strike does +35 damage, but player takes 15 damage per strike.");
        break;
    case SPELL_CAST:
    {
        var_set_bool(res, FALSE);
        if (p_ptr->tim_blood_feast)
        {
            if (!get_check("Cancel the Blood Feast? ")) return;
            set_tim_blood_feast(0, TRUE);
        }
        else
        {
            set_tim_blood_feast(randint1(25) + 25, FALSE);
            var_set_bool(res, TRUE);
        }
        break;
    }
    default:
        default_spell(cmd, res);
        break;
    }
}

void _blood_revenge_spell(int cmd, variant *res)
{
    switch (cmd)
    {
    case SPELL_NAME:
        var_set_string(res, "Blood Revenge");
        break;
    case SPELL_DESC:
        var_set_string(res, "Gives an aura of bloody revenge.  Monsters take damaged based on your cut status.");
        break;
    case SPELL_SPOIL_DESC:
        var_set_string(res, "For 5+d5 rounds, any foe that does X melee damage to the player takes X*C/100 damage in revenge, where C is the player's current cut status. However, this retaliatory damage is bounded between C/10 and 50 per strike.");
        break;
    case SPELL_CAST:
    {
        set_tim_blood_revenge(randint1(5) + 5, FALSE);
        var_set_bool(res, TRUE);
        break;
    }
    default:
        default_spell(cmd, res);
        break;
    }
}

static int _count_blood_potions(void)
{
    int result = 0, i;
    for (i = 0; i < INVEN_PACK; i++)
    {
        object_type *o_ptr = &inventory[i];

        if (!o_ptr->k_idx) continue;

        if (o_ptr->tval == TV_POTION && o_ptr->sval == SV_POTION_BLOOD)
            result += o_ptr->number;
    }

    return result;
}

void _blood_pool_spell(int cmd, variant *res)
{
    switch (cmd)
    {
    case SPELL_NAME:
        var_set_string(res, "Blood Pool");
        break;
    case SPELL_DESC:
        var_set_string(res, "Creates a macabre Potion of Healing made of your own blood.");
        break;
    case SPELL_SPOIL_DESC:
        var_set_string(res, "Create a potion of blood. Player is limited to 30 such potions, and may neither "
                                "drop, throw nor sell them. Quaffing a potion of blood heals 100hp and cures "
                                "blindness, confusion, poison and stuns.");
        break;
    case SPELL_CAST:
    {
        object_type forge;
        int ct = _count_blood_potions();

        if (ct >= 30)
        {
            msg_print("You have too many blood potions at the moment.  Why not drink some?");
            var_set_bool(res, FALSE);
            return;
        }

        msg_print("You feel light headed.");
        object_prep(&forge, lookup_kind(TV_POTION, SV_POTION_BLOOD));

        /* We can't just drop potions on the ground, or the user can spam the spell! */
        if (!inven_carry_okay(&forge))
        {
            msg_print("Your pack is full!  The potion goes sour ...");
            object_prep(&forge, lookup_kind(TV_POTION, SV_POTION_SALT_WATER));
            drop_near(&forge, -1, py, px);
        }
        else
        {
            inven_carry(&forge);
            msg_print("You store your blood for future use.");
        }
        var_set_bool(res, TRUE);
        break;
    }
    default:
        default_spell(cmd, res);
        break;
    }
}

void _blood_explosion_spell(int cmd, variant *res)
{
    switch (cmd)
    {
    case SPELL_NAME:
        var_set_string(res, "Blood Explosion");
        break;
    case SPELL_DESC:
        var_set_string(res, "Damages all living creatures in sight at tremendous cost to your own health.");
        break;
    case SPELL_SPOIL_DESC:
        var_set_string(res, "All living creatures in player's line of sight take 500 damage.");
        break;
    case SPELL_INFO:
        var_set_string(res, info_damage(0, 0, 500));
        break;
    case SPELL_CAST:
    {
        msg_print("You cut too deep ... Your blood explodes!");
        dispel_living(500);
        var_set_bool(res, TRUE);
        break;
    }
    default:
        default_spell(cmd, res);
        break;
    }
}

void _cauterize_wounds_spell(int cmd, variant *res)
{
    switch (cmd)
    {
    case SPELL_NAME:
        var_set_string(res, "Cauterize Wounds");
        break;
    case SPELL_DESC:
        var_set_string(res, "Cures cuts");
        break;
    case SPELL_CAST:
        set_cut(0, TRUE);
        var_set_bool(res, TRUE);
        break;
    default:
        default_spell(cmd, res);
        break;
    }
}

static power_info _powers[] =
{
    { A_CON, {30, 20, 50, _cauterize_wounds_spell} }, 
    { -1, { -1, -1, -1, NULL} }
};

static spell_info _spells[] = 
{
    /*lvl cst fail spell */
    {  1,   1, 20, _blood_flow_spell },
    {  5,  5,  30, _blood_sight_spell},
    { 10, 10,  30, _blood_spray_spell},
    { 15, 20,  30, _blood_bath_spell},
    { 20, 30,  30, _blood_shield_spell},
    { 25, 50,  40, _blood_seeking_spell},
    { 30, 60,  40, _blood_rage_spell},
    { 40, 60,  50, _blood_feast_spell},
    { 42, 60,   0, _blood_revenge_spell},
    { 45,200,   0, _blood_pool_spell},
    { 50,500,  60, _blood_explosion_spell},
    { -1, -1,  -1, NULL}
}; 

static int _get_spells(spell_info* spells, int max)
{
    return get_spells_aux(spells, max, _spells);
}

static int _get_powers(spell_info* spells, int max)
{
    return get_powers_aux(spells, max, _powers);
}

static void _calc_bonuses(void)
{
    p_ptr->regenerate = TRUE;
    if (p_ptr->lev >= 30) res_add(RES_FEAR);

    if (p_ptr->cut > 0)
    {
        int to_h = 0;
        int to_d = 0;
        int to_stealth = 0;
        if (p_ptr->cut >= CUT_MORTAL_WOUND)
        {
            to_h = 25;
            to_d = 25;
            to_stealth = -10;
        }
        else if (p_ptr->cut >= CUT_DEEP_GASH)
        {
            to_h = 15;
            to_d = 15;
            to_stealth = -3;
        }
        else if (p_ptr->cut >= CUT_SEVERE)
        {
            to_h = 8;
            to_d = 8;
            to_stealth = -2;
        }
        else if (p_ptr->cut >= CUT_NASTY)
        {
            to_h = 6;
            to_d = 6;
            to_stealth = -2;
        }
        else if (p_ptr->cut >= CUT_BAD)
        {
            to_h = 4;
            to_d = 4;
            to_stealth = -1;
        }
        else if (p_ptr->cut >= CUT_LIGHT)
        {
            to_h = 2;
            to_d = 2;
            to_stealth = -1;
        }
        else
        {
            to_h = 1;
            to_d = 1;
            to_stealth = -1;
        }
        p_ptr->weapon_info[0].to_h += to_h;
        p_ptr->weapon_info[1].to_h += to_h;
        p_ptr->to_h_m  += to_h;
        p_ptr->weapon_info[0].dis_to_h += to_h;
        p_ptr->weapon_info[1].dis_to_h += to_h;

        p_ptr->weapon_info[0].to_d += to_d;
        p_ptr->weapon_info[1].to_d += to_d;
        p_ptr->to_d_m  += to_d;
        p_ptr->weapon_info[0].dis_to_d += to_d;
        p_ptr->weapon_info[1].dis_to_d += to_d;

        p_ptr->skills.stl += to_stealth;
    }

    if (p_ptr->tim_blood_shield)
    {
        int amt = 100 * (p_ptr->mhp - p_ptr->chp) / p_ptr->mhp; 
        p_ptr->to_a += amt;
        p_ptr->dis_to_a += amt;    
        if (amt > 60)
            p_ptr->reflect = TRUE;
    }

    if (p_ptr->tim_blood_feast)
    {
        p_ptr->weapon_info[0].to_d += 35;
        p_ptr->weapon_info[1].to_d += 35;
        p_ptr->to_d_m  += 35; /* Tentacles, beak, etc. */
        p_ptr->weapon_info[0].dis_to_d += 35;
        p_ptr->weapon_info[1].dis_to_d += 35;
    }
}

static void _calc_weapon_bonuses(object_type *o_ptr, weapon_info_t *info_ptr)
{
    int frac = p_ptr->chp * 100 / p_ptr->mhp;
    if (frac < 20 && p_ptr->lev > 48)
        info_ptr->xtra_blow += 900;
    else if (frac < 40 && p_ptr->lev > 36)
        info_ptr->xtra_blow += 600;
    else if (frac < 60 &&  p_ptr->lev > 24)
        info_ptr->xtra_blow += 400;
    else if (frac < 80 && p_ptr->lev > 12)
        info_ptr->xtra_blow += 200;
    else if (p_ptr->chp < p_ptr->mhp) /* Hack: frac might be 100 if we are just slightly wounded */
        info_ptr->xtra_blow += 100;
}

static void _on_cast(const spell_info *spell)
{
    set_cut(p_ptr->cut + spell->level, FALSE);
    p_ptr->update |= PU_BONUS;
}

static caster_info * _caster_info(void)
{
    static caster_info me = {0};
    static bool init = FALSE;
    if (!init)
    {
        me.magic_desc = "bloodcraft";
        me.options = CASTER_USE_HP;
        me.which_stat = A_CON;
        me.on_cast = _on_cast;
        me.weight = 1000;
        init = TRUE;
    }
    return &me;
}

class_t *blood_knight_get_class_t(void)
{
    static class_t me = {0};
    static bool init = FALSE;

    /* static info never changes */
    if (!init)
    {           /* dis, dev, sav, stl, srh, fos, thn, thb */
    skills_t bs = { 25,  18,  32,   2,  16,   6,  70,  20};
    skills_t xs = { 12,   7,  10,   0,   0,   0,  23,  15};

        me.name = "Blood-Knight";
        me.desc = "A Blood-Knight is a fighter who has delved into the dark arts and can perform "
                  "a limited number of offensive effects using his own health. In addition to the "
                  "HP cost, using an ability also causes bleeding/wounds, with an amount proportional "
                  "to the cost of the ability. Their primary stat for abilities is Con.\n \n"
                  "Blood-Knights are strong in melee, but are very unusual in the fact that the more "
                  "wounded they are, the stronger they become. When damaged, they gain additional "
                  "melee attacks and damage, and moreso the more wounded and cut they become. Indeed, when on the "
                  "brink of death they are the strongest fighters imaginable, and stories of their "
                  "legendary feats abound. Of course, with great power comes great risk of death, "
                  "and you don't recall ever meeting one of these heroes of legend in person!\n \n"
                  "Since the Blood-Knight relies on their own blood for their power, they are restricted "
                  "to only certain races. No non-living race may walk the red path.";

        me.stats[A_STR] =  2;
        me.stats[A_INT] = -2;
        me.stats[A_WIS] = -2;
        me.stats[A_DEX] =  0;
        me.stats[A_CON] =  3;
        me.stats[A_CHR] =  2;
        
        me.base_skills = bs;
        me.extra_skills = xs;
        
        me.life = 120;
        me.base_hp = 20;
        me.exp = 150;
        me.pets = 40;

        me.calc_bonuses = _calc_bonuses;
        me.calc_weapon_bonuses = _calc_weapon_bonuses;
        me.caster_info = _caster_info;
        me.get_spells = _get_spells;
        me.get_powers = _get_powers;
        init = TRUE;
    }

    return &me;
}

