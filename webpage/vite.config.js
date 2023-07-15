import { defineConfig } from 'vite'
import { viteSingleFile } from 'vite-plugin-singlefile'
import solid from 'vite-plugin-solid'
import solidSvg from 'vite-plugin-solid-svg'

export default defineConfig({
  plugins: [solid(), viteSingleFile(), solidSvg()],
  assetsInlineLimit: 40960
})