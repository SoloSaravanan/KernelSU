#include <linux/compiler.h>

extern bool susfs_is_avc_log_spoofing_enabled;

static int avc_spoof_feature_get(u64 *value)
{
	*value = READ_ONCE(susfs_is_avc_log_spoofing_enabled);
	return 0;
}

static int avc_spoof_feature_set(u64 value)
{
	WRITE_ONCE(susfs_is_avc_log_spoofing_enabled, value != 0);
	return 0;
}

static const struct ksu_feature_handler avc_spoof_handler = {
	.feature_id = KSU_FEATURE_AVC_SPOOF,
	.name = "avc_spoof",
	.get_handler = avc_spoof_feature_get,
	.set_handler = avc_spoof_feature_set,
};

void __init ksu_avc_spoof_feature_init(void)
{
	int ret = ksu_register_feature_handler(&avc_spoof_handler);

	if (ret)
		pr_err("Failed to register avc_spoof feature handler: %d\n", ret);
}

void __exit ksu_avc_spoof_feature_exit(void)
{
	ksu_unregister_feature_handler(KSU_FEATURE_AVC_SPOOF);
}
