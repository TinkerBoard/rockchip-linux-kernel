# ROCKCHIP Platform Support
snd-soc-rockchip-i2s-objs := rockchip_i2s.o
snd-soc-rockchip-i2s-tdm-objs := rockchip_i2s_tdm.o
snd-soc-rockchip-multi-dais-objs := rockchip_multi_dais.o rockchip_multi_dais_pcm.o
snd-soc-rockchip-pdm-objs := rockchip_pdm.o
snd-soc-rockchip-spdif-objs := rockchip_spdif.o
snd-soc-rockchip-spdifrx-objs := rockchip_spdifrx.o
snd-soc-rockchip-vad-objs := rockchip_vad.o
ifdef CONFIG_THUMB2_KERNEL
snd-soc-rockchip-vad-$(CONFIG_THUMB2_KERNEL) += vad_preprocess_thumb.o
else
snd-soc-rockchip-vad-$(CONFIG_ARM64) += vad_preprocess_arm64.o
snd-soc-rockchip-vad-$(CONFIG_ARM) += vad_preprocess_arm.o
endif

obj-$(CONFIG_SND_SOC_ROCKCHIP_I2S) += snd-soc-rockchip-i2s.o
obj-$(CONFIG_SND_SOC_ROCKCHIP_I2S_TDM) += snd-soc-rockchip-i2s-tdm.o
obj-$(CONFIG_SND_SOC_ROCKCHIP_MULTI_DAIS) += snd-soc-rockchip-multi-dais.o
obj-$(CONFIG_SND_SOC_ROCKCHIP_PDM) += snd-soc-rockchip-pdm.o
obj-$(CONFIG_SND_SOC_ROCKCHIP_SPDIF) += snd-soc-rockchip-spdif.o
obj-$(CONFIG_SND_SOC_ROCKCHIP_SPDIFRX) += snd-soc-rockchip-spdifrx.o
obj-$(CONFIG_SND_SOC_ROCKCHIP_VAD) += snd-soc-rockchip-vad.o

ccflags-y += -DROCKCHIP_AUDIO

snd-soc-rockchip-da7219-objs := rockchip_da7219.o
snd-soc-rockchip-hdmi-analog-objs := rockchip_hdmi_analog.o
snd-soc-rockchip-hdmi-dp-objs := rockchip_hdmi_dp.o
snd-soc-rockchip-max98090-objs := rockchip_max98090.o
snd-soc-rockchip-multicodecs-objs := rockchip_multicodecs.o
snd-soc-rockchip-rt5645-objs := rockchip_rt5645.o
snd-soc-rockchip-rt5651-rk628-objs := rockchip_rt5651_rk628.o
snd-soc-rockchip-rt5651-tc358749x-objs := rockchip_rt5651_tc358749x.o
snd-soc-rockchip-cdndp-objs := rockchip_cdndp.o
snd-soc-hifiberry-amp-objs := hifiberry_amp.o
snd-soc-hifiberry-dac-objs := hifiberry_dac.o
snd-soc-hifiberry-dacplus-objs := hifiberry_dacplus.o
snd-soc-hifiberry-digi-objs := hifiberry_digi.o
snd-soc-iqaudio-dac-objs := iqaudio-dac.o
snd-soc-iqaudio-digi-objs := iqaudio-digi.o
snd-soc-justboom-dac-objs := justboom-dac.o
snd-soc-justboom-digi-objs := justboom-digi.o

obj-$(CONFIG_SND_SOC_ROCKCHIP_DA7219) += snd-soc-rockchip-da7219.o
obj-$(CONFIG_SND_SOC_ROCKCHIP_HDMI_ANALOG) += snd-soc-rockchip-hdmi-analog.o
obj-$(CONFIG_SND_SOC_ROCKCHIP_HDMI_DP) += snd-soc-rockchip-hdmi-dp.o
obj-$(CONFIG_SND_SOC_ROCKCHIP_MAX98090) += snd-soc-rockchip-max98090.o
obj-$(CONFIG_SND_SOC_ROCKCHIP_MULTICODECS) += snd-soc-rockchip-multicodecs.o
obj-$(CONFIG_SND_SOC_ROCKCHIP_RT5645) += snd-soc-rockchip-rt5645.o
obj-$(CONFIG_SND_SOC_ROCKCHIP_RT5651_RK628) += snd-soc-rockchip-rt5651-rk628.o
obj-$(CONFIG_SND_SOC_ROCKCHIP_RT5651_TC358749) += snd-soc-rockchip-rt5651-tc358749x.o
obj-$(CONFIG_SND_SOC_ROCKCHIP_CDNDP) += snd-soc-rockchip-cdndp.o
obj-$(CONFIG_SND_SOC_HIFIBERRY_AMP) += snd-soc-hifiberry-amp.o
obj-$(CONFIG_SND_SOC_HIFIBERRY_DAC) += snd-soc-hifiberry-dac.o
obj-$(CONFIG_SND_SOC_HIFIBERRY_DACPLUS) += snd-soc-hifiberry-dacplus.o
obj-$(CONFIG_SND_SOC_HIFIBERRY_DIGI) += snd-soc-hifiberry-digi.o
obj-$(CONFIG_SND_SOC_IQAUDIO_DAC) += snd-soc-iqaudio-dac.o
obj-$(CONFIG_SND_SOC_IQAUDIO_DIGI) += snd-soc-iqaudio-digi.o
obj-$(CONFIG_SND_SOC_JUSTBOOM_DAC) += snd-soc-justboom-dac.o
obj-$(CONFIG_SND_SOC_JUSTBOOM_DIGI) += snd-soc-justboom-digi.o
obj-$(CONFIG_SND_SOC_SEEEDVOICEHAT_CARD) += seeedvoicehat/
