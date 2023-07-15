import { createSignal } from 'solid-js'
import solidLogo from './assets/solid.svg'
import './App.css'
import chilcken from "./assets/5.png"
import v1 from "./assets/2.png"
import v2 from "./assets/3.png"
import v3 from "./assets/4.png"
import gou from "./assets/1.png"


function App() {
  const [count, setCount] = createSignal(0)


  return (
    <>
      <div class="App">
        <div class="top">
          <img src={chilcken} />

        </div>
        <div class="mid">

          <img src={v1} />
          <img src={v2} />
          <img src={v3} />

        </div>
        <div class="btm" onClick={() => fetch("/req")}>
          <img src={gou} />
        </div>
      </div>




    </>
  )
}

export default App
