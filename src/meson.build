nvapi_src = files([
  'util/util_string.cpp',
  'util/util_env.cpp',
  'util/util_log.cpp',
  'sysinfo/vulkan.cpp',
  'sysinfo/nvml.cpp',
  'sysinfo/nvapi_output.cpp',
  'sysinfo/nvapi_adapter.cpp',
  'sysinfo/nvapi_adapter_registry.cpp',
  'resource_factory.cpp',
  'd3d/lfx.cpp',
  'd3d/nvapi_d3d_instance.cpp',
  'd3d/nvapi_d3d_low_latency_device.cpp',
  'd3d11/nvapi_d3d11_device.cpp',
  'd3d12/nvapi_d3d12_device.cpp',
  'nvapi_globals.cpp',
  'nvapi.cpp',
  'nvapi_d3d.cpp',
  'nvapi_d3d11.cpp',
  'nvapi_d3d12.cpp',
  'nvapi_disp.cpp',
  'nvapi_drs.cpp',
  'nvapi_gpu.cpp',
  'nvapi_mosaic.cpp',
  'nvapi_sys.cpp',
  'nvapi_interface.cpp',
])

arch_dir_prefix = target_machine.cpu_family() == 'x86_64' ? 'x86_64-' : 'i386-'
install_dir_windows = install_dir / arch_dir_prefix + 'windows'

nvapi_dll = shared_library('nvapi'+target_suffix, [ nvapi_src, dxvk_nvapi_version ],
  name_prefix         : '',
  dependencies        : [ lib_dxgi, lib_d3d11, lib_version ],
  include_directories : [ vk_headers ],
  install             : true,
  install_dir         : install_dir_windows)
