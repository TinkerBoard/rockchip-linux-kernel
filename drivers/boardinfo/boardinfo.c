#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/of_platform.h>
#include <linux/of_gpio.h>
#include <linux/iio/iio.h>
#include <linux/iio/machine.h>
#include <linux/iio/driver.h>
#include <linux/iio/consumer.h>
#include <linux/proc_fs.h>

static int projectid = -1, boardid = -1, ddrid = -1, emmcid = -1, odmid = -1;
static char *boardinfo, *boardver, *ddr, *emmc, *odm;
static int emmc0_gpio = 0, emmc1_gpio = 0, init_done = 0;

static int all_show(struct seq_file *m, void *v)
{
	seq_printf(m, "boardinfo:\t%s\n", boardinfo);
	seq_printf(m, "projectid:\t%d\n", projectid);
	seq_printf(m, "boardver:\t%s\n", boardver);
	seq_printf(m, "boardid:\t%d\n", boardid);
	seq_printf(m, "ddr:\t\t%s\n", ddr);
	seq_printf(m, "ddrid:\t\t%d\n", ddrid);
	seq_printf(m, "emmc:\t\t%s\n", emmc);
	seq_printf(m, "emmcid:\t\t%d\n", emmcid);
	seq_printf(m, "odm:\t\t%s\n", odm);
	seq_printf(m, "odmid:\t\t%d\n", odmid);
	return 0;
}

static int all_open(struct inode *inode, struct file *file)
{
	return single_open(file, all_show, NULL);
}

static const struct proc_ops all_ops = {
	.proc_open = all_open,
	.proc_read = seq_read,
};

static int info_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%s\n", boardinfo);
	return 0;
}

static int info_open(struct inode *inode, struct file *file)
{
	return single_open(file, info_show, NULL);
}

static const struct proc_ops info_ops = {
	.proc_open = info_open,
	.proc_read = seq_read,
};

static int projectid_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%d\n", projectid);
	return 0;
}

static int projectid_open(struct inode *inode, struct file *file)
{
	return single_open(file, projectid_show, NULL);
}

static const struct proc_ops projectid_ops = {
	.proc_open = projectid_open,
	.proc_read = seq_read,
};

static int ver_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%s\n", boardver);
	return 0;
}

static int ver_open(struct inode *inode, struct file *file)
{
	return single_open(file, ver_show, NULL);
}

static const struct proc_ops ver_ops = {
	.proc_open = ver_open,
	.proc_read = seq_read,
};

static int boardid_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%d\n", boardid);
	return 0;
}

static int boardid_open(struct inode *inode, struct file *file)
{
	return single_open(file, boardid_show, NULL);
}

static const struct proc_ops boardid_ops = {
	.proc_open = boardid_open,
	.proc_read = seq_read,
};

static int ddr_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%s\n", ddr);
	return 0;
}

static int ddr_open(struct inode *inode, struct file *file)
{
	return single_open(file, ddr_show, NULL);
}

static const struct proc_ops ddr_ops = {
	.proc_open = ddr_open,
	.proc_read = seq_read,
};

static int ddrid_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%d\n", ddrid);
	return 0;
}

static int ddrid_open(struct inode *inode, struct file *file)
{
	return single_open(file, ddrid_show, NULL);
}

static const struct proc_ops ddrid_ops = {
	.proc_open = ddrid_open,
	.proc_read = seq_read,
};

static int emmc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%s\n", emmc);
	return 0;
}

static int emmc_open(struct inode *inode, struct file *file)
{
	return single_open(file, emmc_show, NULL);
}

static const struct proc_ops emmc_ops = {
	.proc_open = emmc_open,
	.proc_read = seq_read,
};

static int emmcid_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%d\n", emmcid);
	return 0;
}

static int emmcid_open(struct inode *inode, struct file *file)
{
	return single_open(file, emmcid_show, NULL);
}

static const struct proc_ops emmcid_ops = {
	.proc_open = emmcid_open,
	.proc_read = seq_read,
};

static int odm_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%s\n", odm);
	return 0;
}

static int odm_open(struct inode *inode, struct file *file)
{
	return single_open(file, odm_show, NULL);
}

static const struct proc_ops odm_ops = {
	.proc_open = odm_open,
	.proc_read = seq_read,
};

static int odmid_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%d\n", odmid);
	return 0;
}

static int odmid_open(struct inode *inode, struct file *file)
{
	return single_open(file, odmid_show, NULL);
}

static const struct proc_ops odmid_ops = {
	.proc_open = odmid_open,
	.proc_read = seq_read,
};

static int boardinfo_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int ret, raw, vref, bits;
	int vresult, id0, id1;
	struct iio_channel *channels;
	struct proc_dir_entry* file;
	const char *compatible, *channel_name;

	if (device_property_read_string(dev, "compatible", &compatible)) {
		printk("[boardinfo] Failed to read compatible");
		return -ENODEV;
	}
	printk("boardinfo: initialized %s\n", compatible);

	if (strcmp(compatible, "boardinfo") == 0) {
		emmc0_gpio = of_get_named_gpio(dev->of_node, "emmc0-gpios", 0);
		if (!gpio_is_valid(emmc0_gpio)) {
			printk("[boardinfo] No emmc0-gpio pin available in boardinfo\n");
			return -ENODEV;
		} else {
			ret = devm_gpio_request_one(dev, emmc0_gpio, GPIOF_DIR_IN, "GPIO_EMMC0");
			if (ret < 0) {
				printk("[boardinfo] Failed to request EMMC0 gpio: %d\n", ret);
				return ret;
			}
		}

		emmc1_gpio = of_get_named_gpio(dev->of_node, "emmc1-gpios", 0);
		if (!gpio_is_valid(emmc1_gpio)) {
			printk("[boardinfo] No emmc1-gpio pin available in boardinfo\n");
			return -ENODEV;
		} else {
			ret = devm_gpio_request_one(dev, emmc1_gpio, GPIOF_DIR_IN, "GPIO_EMMC1");
			if (ret < 0) {
				printk("[boardinfo] Failed to request EMMC1 gpio: %d\n", ret);
				return ret;
			}
		}

		id0 = gpio_get_value(emmc0_gpio);
		id1 = gpio_get_value(emmc1_gpio);

		emmcid = (id1 << 1) + id0;

		switch(emmcid) {
			case 0:
				emmc = "16GB";
				break;
			case 1:
				emmc = "32GB";
				break;
			case 2:
				emmc = "64GB";
				break;
			case 3:
				emmc = "NONE";
				break;
			default:
				emmc = "unknown";
		}

		file = proc_create("emmc", 0444, NULL, &emmc_ops);
		if (!file)
			return -ENOMEM;

		file = proc_create("emmcid", 0444, NULL, &emmcid_ops);
		if (!file)
			return -ENOMEM;
	} else {
		if (device_property_read_string(dev, "io-channel-names", &channel_name)) {
			printk("[boardinfo][iio] Failed to read io-channel-names");
			return -ENODEV;
		}

		channels = devm_iio_channel_get(dev, channel_name);
		if (IS_ERR(channels)) {
			printk("[boardinfo][iio] Failed to get channels\n");
			return -ENODEV;
		} else {
			ret = iio_read_channel_raw(channels, &raw);
			if (ret < 0) {
				printk("[boardinfo][iio] Failed to read channel raw\n");
				return ret;
			}

			ret = iio_read_channel_scale(channels, &vref, &bits);
			if (ret < 0) {
				printk("[boardinfo][iio] Failed to read channel scale\n");
				return ret;
			}
		}

		vresult = vref * raw / ((2 << (bits - 1)) - 1);

		if (vresult < 1950 && vresult > 1650)
			ret = 18;
		else if (vresult < 1650 && vresult > 1350)
			ret = 15;
		else if (vresult < 1350 && vresult > 1050)
			ret = 12;
		else if (vresult < 1050 && vresult > 750)
			ret = 9;
		else if (vresult < 750 && vresult > 450)
			ret = 6;
		else if (vresult < 450 && vresult > 150)
			ret = 3;
		else if (vresult < 150)
			ret = 0;

		if (strcmp(compatible, "ADC1-PCBID") == 0) {
			boardid = ret;

			switch(boardid) {
				case 18:
					boardver = "1.00";
					break;
				case 15:
					boardver = "1.01";
					break;
				case 12:
					boardver = "1.02";
					break;
				case 9:
				case 6:
				case 3:
				case 0:
				default:
					boardver = "unknown";
			}

			file = proc_create("boardver", 0444, NULL, &ver_ops);
			if (!file)
				return -ENOMEM;

			file = proc_create("boardid", 0444, NULL, &boardid_ops);
			if (!file)
				return -ENOMEM;
		} else if (strcmp(compatible, "ADC3-RAMID") == 0) {
			ddrid = ret;

			switch(ddrid) {
				case 18:
					ddr = "2GB";
					break;
				case 15:
					ddr = "4GB";
					break;
				case 12:
					ddr = "8GB";
					break;
				case 9:
				case 6:
				case 3:
				case 0:
				default:
					ddr = "unknown";
			}

			file = proc_create("ddr", 0444, NULL, &ddr_ops);
			if (!file)
				return -ENOMEM;

			file = proc_create("ddrid", 0444, NULL, &ddrid_ops);
			if (!file)
				return -ENOMEM;
		} else if (strcmp(compatible, "ADC4-ODMID") == 0) {
			odmid = ret;

			switch(odmid) {
				case 18:
					odm = "Tinker Board 3";
					break;
				case 15:
					odm = "Sanden";
					break;
				case 12:
				case 9:
				case 6:
				case 3:
				case 0:
				default:
					odm = "unknown";
			}

			file = proc_create("odm", 0444, NULL, &odm_ops);
			if (!file)
				return -ENOMEM;

			file = proc_create("odmid", 0444, NULL, &odmid_ops);
			if (!file)
				return -ENOMEM;
		} else if (strcmp(compatible, "ADC5-PRJID") == 0) {
			projectid = ret;

			switch(projectid) {
				case 18:
					if (odmid == 15)
						boardinfo = "Sanden - SKU1";
					else
						boardinfo = "Tinker Board 3 - SKU1";
					break;
				case 15:
					boardinfo = "Tinker Board 3 - SKU2";
					break;
				case 12:
					boardinfo = "Tinker Board 3 - SKU3";
					break;
				case 9:
				case 6:
				case 3:
				case 0:
				default:
					boardinfo = "unknown";
			}

			file = proc_create("boardinfo", 0444, NULL, &info_ops);
			if (!file)
				return -ENOMEM;

			file = proc_create("projectid", 0444, NULL, &projectid_ops);
			if (!file)
				return -ENOMEM;
		}
	}

	if (!init_done) {
		file = proc_create("boardinfo_all", 0444, NULL, &all_ops);
		if (!file)
			return -ENOMEM;
		else
			init_done = 1;
	}

	return 0;
}

int get_pcbid(void)
{
	return boardid;
}
EXPORT_SYMBOL_GPL(get_pcbid);

int get_prjid(void)
{
	return projectid;
}
EXPORT_SYMBOL_GPL(get_prjid);

int get_ramid(void)
{
	return ddrid;
}
EXPORT_SYMBOL_GPL(get_ramid);

int get_emmcid(void)
{
	return emmcid;
}
EXPORT_SYMBOL_GPL(get_emmcid);

int get_odmid(void)
{
	return odmid;
}
EXPORT_SYMBOL_GPL(get_odmid);

static int boardinfo_remove(struct platform_device *pdev)
{
	gpio_free(emmc0_gpio);
	gpio_free(emmc1_gpio);

	return 0;
}

static const struct of_device_id of_boardinfo_match[] = {
	{ .compatible = "boardinfo", },
	{ .compatible = "ADC1-PCBID", },
	{ .compatible = "ADC3-RAMID", },
	{ .compatible = "ADC4-ODMID", },
	{ .compatible = "ADC5-PRJID", },
	{},
};
MODULE_DEVICE_TABLE(of, of_boardinfo_match);

static struct platform_driver boardinfo_driver = {
	.probe		= boardinfo_probe,
	.remove		= boardinfo_remove,
	.driver = {
		.name	= "boardinfo",
		.of_match_table = of_match_ptr(of_boardinfo_match),
	},
};

module_platform_driver(boardinfo_driver);

MODULE_ALIAS("platform:boardinfo");
MODULE_AUTHOR("Frank Chiang <frank_chiang@asus.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Driver to set Board Information");
