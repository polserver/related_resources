// by Hugo P.L.
// Executa a animação de criação para os elementais e o corpse.
if (((me.graphic = 0x0f)or(me.graphic = 0x10)or(me.graphic = 0x0e)or(me.graphic = 0x0d)or(me.graphic = 0x08)))
    case (me.graphic)
        0x0D://Air elemental
            PlaySoundEffect(me, 0x108);
        0x0E://Earth elemental
            PlaySoundEffect(me, 0x10D);
        0x0F://Fire elemental
            PlaySoundEffect(me, 0x116);
        0x10://Water elemental
            PlaySoundEffect(me, 0x118);
        0x08://Corpser
            PlaySoundEffect(me, 0x162);
    endcase
    Performaction( me, 0x000c);
    sleep(5);
endif