#############################################################
#
# dejavu fonts
#
#############################################################

DEJAVU_FONTS_VERSION:=2.34
DEJAVU_FONTS_SOURCE:=dejavu-fonts-ttf-$(DEJAVU_FONTS_VERSION).tar.bz2
DEJAVU_FONTS_SITE:=http://downloads.sourceforge.net/project/dejavu/dejavu/$(DEJAVU_FONTS_VERSION)

define DEJAVU_FONTS_INSTALL_TARGET_CMDS
	mkdir -p $(TARGET_DIR)/usr/share/fonts/dejavu
	cp -a $(@D)/ttf/*.ttf $(TARGET_DIR)/usr/share/fonts/dejavu
endef

$(eval $(generic-package))
