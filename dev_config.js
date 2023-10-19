{
	"service" : 
	{
		"api" : "fastcgi",
		"port" : 7777,
		"disable_global_exit_handling" : true
	},
    "file_server" : 
	{
		"enable" : true,
		"document_root" : "."
	},
	"core":
	{
		"host":"103.31.126.65",
		"port":5678,
		"queue_size": 10000,
		"worker_count": 12,
		"media_queue_size": 10000,
		"media_worker_count": 5,
		"push_queue_size": 10000,
		"push_worker_count": 5,
		"udp_host":"103.31.126.65",
		"udp_port": 5680
	},
	"settings" :
	{
		"init_fake_db": false,
		"production_mode": false,
        "root_storage_dir": "v1/AUTH_e101a72b9d35432f96976a791d13ffc1/viettalk2",
        "http_host": "http://vt2-swift.wala.vn"
	}
}
