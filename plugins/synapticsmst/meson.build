cargs = ['-DG_LOG_DOMAIN="FuPluginSynapticsMST"']

shared_module('fu_plugin_synapticsmst',
  sources : [
    'fu-plugin-synapticsmst.c',
    'synapticsmst-common.c',
    'synapticsmst-device.c',
  ],
  include_directories : [
    include_directories('../..'),
    include_directories('../../src'),
    include_directories('../../libfwupd'),
  ],
  install : true,
  install_dir: plugin_dir,
  c_args : [
      cargs,
    ],
  dependencies : [
    plugin_deps,
    efivar,
  ],
  # https://github.com/hughsie/fwupd/issues/207
  override_options : [
    'werror=false',
  ]
)

if get_option('tests')
  cargs += '-DFU_OFFLINE_DESTDIR="/tmp/fwupd-self-test"'
  cargs += '-DPLUGINBUILDDIR="' + meson.current_build_dir() + '"'
  cargs += '-DSOURCEDIR="' + meson.current_source_dir() + '"'
  e = executable(
    'synapticsmst-self-test',
    sources : [
      'fu-self-test.c',
    ],
    include_directories : [
      include_directories('../..'),
      include_directories('../../src'),
      include_directories('../../libfwupd'),
    ],
    dependencies : [
      plugin_deps,
      sqlite,
      valgrind,
    ],
    link_with : [
      fwupd,
      libfwupdprivate,
    ],
    c_args : [
      cargs,
    ],
  )
  test('synapticsmst-self-test', e,
    env: ['FWUPD_LOCALSTATEDIR=/tmp/fwupd-self-test/var'])
endif
