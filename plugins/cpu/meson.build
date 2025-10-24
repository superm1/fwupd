hsi or subdir_done()

cargs = ['-DG_LOG_DOMAIN="FuPluginCpu"']
plugins += {meson.current_source_dir().split('/')[-1]: true}

plugin_quirks += files('cpu.quirk')
plugin_builtins += static_library('fu_plugin_cpu',
  sources: [
    'fu-cpu-plugin.c',
    'fu-cpu-device.c',
  ],
  include_directories: plugin_incdirs,
  link_with: plugin_libs,
  c_args: cargs,
  dependencies: plugin_deps,
)

code = '''
#if !__has_attribute (__noclone__)
#error symver attribute not supported
#endif
static void __attribute__((noinline,noclone)) f(void) {}
'''

# verify the compiler knows what to do
if host_cpu == 'x86_64' and cc.has_argument('-fcf-protection')
  build_fwupdcethelper = cc.compiles(code,
    name: '__attribute__((noinline,noclone))',
  )
else
  build_fwupdcethelper = false
endif

if build_fwupdcethelper
  libfwupdcethelper = static_library('fwupdcethelper',
    sources: [
      'fu-cpu-helper-cet-common.S',
    ],
    include_directories: [
      root_incdir,
    ],
    c_args: ['-fcf-protection=none'],
    install: false,
  )

  executable(
    'fwupd-detect-cet',
    sources: [
      'fu-cpu-helper-cet.c',
    ],
    include_directories: [
      root_incdir,
    ],
    link_with: [
      libfwupdcethelper,
    ],
    c_args: ['-fcf-protection=full'],
    install: true,
    install_dir: join_paths(libexecdir, 'fwupd')
  )
endif

# AMD SB-7055 helper
if host_cpu == 'x86_64'
  libfwupdamdsb7055helper = static_library('fwupdamdsb7055helper',
    sources: [
      'fu-cpu-helper-amd-sb7055-common.S',
    ],
    include_directories: [
      root_incdir,
    ],
    install: false,
  )

  executable(
    'fwupd-detect-amd-sb7055',
    sources: [
      'fu-cpu-helper-amd-sb7055.c',
    ],
    include_directories: [
      root_incdir,
    ],
    link_with: [
      libfwupdamdsb7055helper,
    ],
    install: true,
    install_dir: join_paths(libexecdir, 'fwupd')
  )
endif
