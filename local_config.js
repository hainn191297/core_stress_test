{
    "service" :
    {
      "api" : "http",
      "ip" : "0.0.0.0",
      "port" : 8088,
      "disable_global_exit_handling" : true
    },
    "http" :
    {
      "script" : "/vt"
    },
    "file_server" :
    {
      "enable" : true,
      "document_root" : "."
    },
    "core" :
    {
      "host":"127.0.0.1",
      "bind_host":"0.0.0.0",
      "port":5678,
      "queue_size": 1000,
      "worker_count": 4,
      "media_queue_size": 1000,
      "media_worker_count": 5,
      "push_queue_size": 1000,
      "push_worker_count": 5,
      "udp_host":"127.0.0.1",
      "udp_port": 8994
    },
    "settings" :
    {
	"swift_container": "viettalk2",
		"swift_username_admin": "admin",
		"swift_password_admin": "97ea37eadd4340d8",
		"swift_tenantname_admin": "admin",
		"keystone_auth_url": "http://10.84.5.161:5000/v2.0/tokens",
		"swift_username_client": "demo",
		"swift_password_client": "73c6df61edd54636",
		"swift_tenantname_client": "demo",
	    	"init_fake_db": false,
		"production_mode": false,
	    	"swift_host": "http://vt2-swift.wala.vn/v1",
		"swift_client": "http://cdn-vt2.wala.vn/v1",
		"mynumber_url": "http://vt2-stag-app01:4001/v3"
    }
}

