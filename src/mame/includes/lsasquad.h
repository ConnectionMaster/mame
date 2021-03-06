// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria

#include "machine/gen_latch.h"
#include "machine/input_merger.h"
#include "machine/taito68705interface.h"
#include "emupal.h"

class lsasquad_state : public driver_device
{
public:
	lsasquad_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_videoram(*this, "videoram"),
		m_scrollram(*this, "scrollram"),
		m_spriteram(*this, "spriteram"),
		m_priority_prom(*this, "prio_prom"),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_soundlatch(*this, "soundlatch"),
		m_soundlatch2(*this, "soundlatch2"),
		m_soundnmi(*this, "soundnmi"),
		m_bmcu(*this, "bmcu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette") { }

	void lsasquad(machine_config &config);
	void daikaiju(machine_config &config);
	void storming(machine_config &config);

protected:
	virtual void machine_start() override;

private:
	/* memory pointers */
	required_shared_ptr<uint8_t> m_videoram;
	required_shared_ptr<uint8_t> m_scrollram;
	required_shared_ptr<uint8_t> m_spriteram;
	required_region_ptr<uint8_t> m_priority_prom;

	/* devices */
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
	required_device<generic_latch_8_device> m_soundlatch;
	optional_device<generic_latch_8_device> m_soundlatch2;
	optional_device<input_merger_device> m_soundnmi;
	optional_device<taito68705_mcu_device> m_bmcu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;

	void lsasquad_bankswitch_w(uint8_t data);
	void lsasquad_sh_nmi_disable_w(uint8_t data);
	void lsasquad_sh_nmi_enable_w(uint8_t data);
	uint8_t lsasquad_sound_status_r();
	uint8_t daikaiju_sound_status_r();

	uint8_t lsasquad_mcu_status_r();
	uint8_t daikaiju_mcu_status_r();
	void unk(uint8_t data);
	uint32_t screen_update_lsasquad(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_daikaiju(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	TIMER_CALLBACK_MEMBER(nmi_callback);
	void draw_layer( bitmap_ind16 &bitmap, const rectangle &cliprect, uint8_t *scrollram );
	int draw_layer_daikaiju( bitmap_ind16 &bitmap, const rectangle &cliprect, int offs, int  * previd, int type );
	void drawbg( bitmap_ind16 &bitmap, const rectangle &cliprect, int type );
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect, uint8_t priority );
	void daikaiju_map(address_map &map);
	void daikaiju_sound_map(address_map &map);
	void lsasquad_map(address_map &map);
	void lsasquad_sound_map(address_map &map);
	void storming_map(address_map &map);
};
