open System
open System.Threading

type Field = bool [,]

let createEmptyField width height =
    Array2D.zeroCreate height width

let initField (width:int, height:int) =
    let random = System.Random(1000)
    Array2D.init height width (fun _ _ -> match random.Next(2) with
        | 0 -> false
        | _ -> true)        

let cellState field x y =
    let width = Array2D.length2 field
    let height = Array2D.length1 field
    if not (0 <= x && x < width && 0 <= y && y < height) then false
    else field.[y, x]

let neighboursCount field (x:int, y:int) =
    let f = cellState field
    [|
        for dx in -1..1 do
            for dy in -1..1 ->
                if dx = 0 && dy = 0 then 0
                else f (dx + x) (dy + y) |> (fun alive -> if alive then 1 else 0)
    |] |> Array.sum

let shouldBeAlive cellAlive neighbours =
    match (cellAlive, neighbours) with
        | (true, 2) -> true
        | (_, 3) -> true
        | (_, _) -> false

let dump field (width: int, height: int) = 
    let charField = Array2D.map (fun cell -> if cell then 'o' else '.') field
    let mutable buf = ""
    charField |> Array2D.iteri (fun y x cell -> 
        if x = width - 1 
        then buf <- buf + cell.ToString() + "\r\n"
        else buf <- buf + cell.ToString())
    printf("%s") buf

let consoleClear = Console.Clear()

let nextGen field =
    field |> Array2D.mapi (fun y x cell -> (neighboursCount field (x,y)) |> shouldBeAlive cell)

let loop width height = 
    let rec go field width height =
        consoleClear
        dump field (width, height)
        let newField = nextGen field
        Thread.Sleep(100)
        go newField width height
    let field = initField(width, height)
    go field width height |> ignore

[<EntryPoint>]
let main argv = 
    let width = 40
    let height = 20
    loop width height
    0 // return an integer exit code
