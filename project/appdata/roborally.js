(function(factory) {
  if(!window["Roborally"])
  {
    window["Roborally"] = {} ;
  }
  factory(window["Roborally"])
})(function (Roborally) {

  const tile_types = {
    /*  0 */  BELT_E : 0,
    /*  1 */  BELT_N: 1,
    /*  2 */  BELT_W: 2,
    /*  3 */  BELT_S: 3,
    /*  4 */  TURN_SE: 4,
    /*  5 */  TURN_SW: 5,
    /*  6 */  TURN_EN: 6,
    /*  7 */  TURN_WN: 7,
    /*  8 */  TURN_NW: 8,
    /*  9 */  TURN_NE: 9,
    /* 10 */  TURN_WS: 10,
    /* 11 */  TURN_ES: 11,
    /* 12 */  JOIN_S_TO_E: 12, 
    /* 13 */  JOIN_S_TO_W: 13, 
    /* 14 */  JOIN_E_TO_N: 14, 
    /* 15 */  JOIN_W_TO_N: 15, 
    /* 16 */  JOIN_N_TO_E: 16, 
    /* 17 */  JOIN_N_TO_W: 17, 
    /* 18 */  JOIN_W_TO_S: 18, 
    /* 19 */  JOIN_E_TO_S: 19, 
    /* 20 */  JOIN_NS_TO_E: 20, 
    /* 21 */  JOIN_EW_TO_N: 21, 
    /* 22 */  JOIN_NS_TO_W: 22, 
    /* 23 */  JOIN_EW_TO_S: 23, 
    /* 24 */  FAST_BELT_E: 24,
    /* 25 */  FAST_BELT_N: 25,
    /* 26 */  FAST_BELT_W: 26,
    /* 27 */  FAST_BELT_S: 27,
    /* 28 */  FAST_TURN_SE: 28,
    /* 29 */  FAST_TURN_SW: 29,
    /* 30 */  FAST_TURN_EN: 30,
    /* 31 */  FAST_TURN_WN: 31,
    /* 32 */  FAST_TURN_NW: 32,
    /* 33 */  FAST_TURN_NE: 33,
    /* 34 */  FAST_TURN_WS: 34,
    /* 35 */  FAST_TURN_ES: 35,
    /* 36 */  FAST_JOIN_S_TO_E: 36, 
    /* 37 */  FAST_JOIN_S_TO_W: 37, 
    /* 38 */  FAST_JOIN_E_TO_N: 38, 
    /* 39 */  FAST_JOIN_W_TO_N: 39, 
    /* 40 */  FAST_JOIN_N_TO_E: 40, 
    /* 41 */  FAST_JOIN_N_TO_W: 41, 
    /* 42 */  FAST_JOIN_W_TO_S: 42, 
    /* 43 */  FAST_JOIN_E_TO_S: 43, 
    /* 44 */  FAST_JOIN_NS_TO_E: 44, 
    /* 45 */  FAST_JOIN_EW_TO_N: 45, 
    /* 46 */  FAST_JOIN_NS_TO_W: 46, 
    /* 47 */  FAST_JOIN_EW_TO_S: 47, 
    /* 48 */  ROTATE_RIGHT: 48, 
    /* 49 */  ROTATE_LEFT: 49, 
    /* 50 */  NOTHING: 50,
    /* 51 */  NONE: 51
  } ;

  const robot_states = {
    EAST: 0,
    NORTH: 1,
    WEST: 2,
    SOUTH: 3,
    DEAD: 4
  } ;

  const robot_moves = {
    FORWARD_1: 0,
    FORWARD_2: 1,
    FORWARD_3: 2,
    BACKWARD_1: 3,
    TURN_LEFT: 4,
    TURN_RIGHT: 5,
    U_TUEN: 6
  } ;

  let board_image = document.getElementById("board") ;
  let tile_size = board_image.viewBox.baseVal.width ;

  let board = {} ;

  let robot = { type : 'robot', line : 0, column : 0, state : robot_states.DEAD, instance : undefined } ;
  let prev_robot = { type : 'prev_robot', line : 0, column : 0, state : robot_states.DEAD, instance : undefined } ;

  function update_view() {
    const elements = board_image.querySelectorAll(".rr-element")
    if(elements.length == 0) return ;
    bbox = [
      elements[0].position[0],
      elements[0].position[1],
      elements[0].position[0],
      elements[0].position[1],
    ]
    for(let i = 1; i < elements.length; ++i) {
      e = elements[i]
      bbox[0] = Math.min(bbox[0], e.position[0]) ;
      bbox[1] = Math.min(bbox[1], e.position[1]) ;
      bbox[2] = Math.max(bbox[2], e.position[0]) ;
      bbox[3] = Math.max(bbox[3], e.position[1]) ;
    }

    const lmin = bbox[0] * tile_size ;
    const cmin = bbox[1] * tile_size ;
    const lsize = (bbox[2]-bbox[0]+1)*tile_size ;
    const csize = (bbox[3]-bbox[1]+1)*tile_size ;
    board_image.setAttribute('viewBox', `${lmin} ${cmin} ${lsize} ${csize}`) ;
  }

  function put_element(name, line, column) {
    let instance = document.createElementNS('http://www.w3.org/2000/svg', 'use') ;
    instance.setAttributeNS('http://www.w3.org/1999/xlink', 'xlink:href', `#${name}`) ;
    instance.setAttribute("x", `${column * tile_size}`) ;
    instance.setAttribute("y", `${line * tile_size}`) ;
    instance.classList.add("rr-element") ;
    instance.classList.add(`type-${name}`) ;
    instance.position = [line, column] ;
    board_image.appendChild(instance) ;
    return instance ;
  }

  const tile_parameters = [
    {
      name : 'forward',
      begin : tile_types.BELT_E,
      end : tile_types.TURN_SE
    },
    {
      name : 'turn',
      begin : tile_types.TURN_SE,
      end : tile_types.JOIN_S_TO_E
    },
    {
      name : 'perp_join',
      begin : tile_types.JOIN_S_TO_E,
      end : tile_types.JOIN_NS_TO_E
    },
    {
      name : 'opp_join',
      begin : tile_types.JOIN_NS_TO_E,
      end : tile_types.FAST_BELT_E
    },
    {
      name : 'fast_forward',
      begin : tile_types.FAST_BELT_E,
      end : tile_types.FAST_TURN_SE
    },
    {
      name : 'fast_turn',
      begin : tile_types.FAST_TURN_SE,
      end : tile_types.FAST_JOIN_S_TO_E
    },
    {
      name : 'fast_perp_join',
      begin : tile_types.FAST_JOIN_S_TO_E,
      end : tile_types.FAST_JOIN_NS_TO_E
    },
    {
      name : 'fast_opp_join',
      begin : tile_types.FAST_JOIN_NS_TO_E,
      end : tile_types.ROTATE_RIGHT
    },
    {
      name : 'rotate',
      begin : tile_types.ROTATE_RIGHT,
      end : tile_types.NOTHING
    }
  ] ;

  function put_type(type, line, column) {
    const centerx = (column + 0.5) * tile_size ;
    const centery = (line + 0.5) * tile_size ;

    for(const param of tile_parameters) {
      if(type >= param.begin && type < param.end) {
        let instance = put_element(param.name, line, column) ;
        const range = param.end - param.begin ;
        const offset = type - param.begin ;
        let transform = `translate(${centerx}, ${centery})` ;
        if(range != 4) {
          const scalex = -2*(offset % 2) + 1 ;
          transform += `scale(${scalex}, 1) ` ;
        }
        if(range > 2) {
          const angle = range > 4 ? offset / 2 | 0 : offset ;
          transform += `rotate(${-90 * angle}) ` ;
        }
        transform += `translate(${-centerx}, ${-centery})` ;
        instance.setAttribute("transform", transform) ;
        return ;
      }
    }
  }

  function draw_robot(robot_data) {
    let instance = robot_data.instance ;
    if(!instance) {
      instance = put_element(robot_data.type, robot_data.line, robot_data.column) ;
      robot_data.instance = instance ;
      instance.addEventListener('click', (e) => {
        robot_data.state = (robot_data.state + 1) % 4 ;
        draw_robot(robot_data) ;
      }) ;
    } else {
      instance.setAttribute("x", `${robot.column * tile_size}`) ;
      instance.setAttribute("y", `${robot.line * tile_size}`) ;
    }
    instance.classList.remove("rr-element") ;
    instance.id = `the_${robot_data.type}` ;
    if(robot_data.state == robot_states.DEAD) {
      instance.style.display = 'none' ;
    } else {
      instance.style.display = 'inline' ;
      const centerx = (robot_data.column + 0.5) * tile_size ;
      const centery = (robot_data.line + 0.5) * tile_size ;
      instance.setAttribute('transform', `rotate(${-90*robot_data.state}, ${centerx}, ${centery})`) ;
    }
  }

  function draw_board() {
    for(const tile of board) {
      let instance = put_element("background", tile.line, tile.column) ;
      instance.addEventListener('click', (e) => {
        robot.line = e.target.position[0] ;
        robot.column = e.target.position[1] ;
        if(robot.state == robot_states.DEAD) {
          robot.state = robot_states.NORTH ;
        }
        draw_robot(robot) ;
      })
    }

    draw_robot(prev_robot) ;
    draw_robot(robot) ;

    for(const tile of board) {
      put_type(tile.type, tile.line, tile.column) ;
    }

    update_view() ;
  }

  function get_board() {
    let xmlHttp = new XMLHttpRequest();
    xmlHttp.onreadystatechange = function() { 
      if (xmlHttp.readyState == 4 && xmlHttp.status == 200) {
        board = JSON.parse(xmlHttp.responseText) ;
        draw_board() ;
      }
    }
    xmlHttp.open("GET", "/board", true);
    xmlHttp.send(null);
  }

  function move_robot(move) {
    let xmlHttp = new XMLHttpRequest();
    xmlHttp.onreadystatechange = function() { 
      if (xmlHttp.readyState == 4 && xmlHttp.status == 200) {
        res = JSON.parse(xmlHttp.responseText) ;
        prev_robot.line = robot.line ;
        prev_robot.column = robot.column ;
        prev_robot.state = robot.state ;
        draw_robot(prev_robot)

        robot.line = res.line ;
        robot.column = res.column ;
        robot.state = res.state ;
        draw_robot(robot) ;
      }
    }
    let path = "/move" ;
    path += `?line=${robot.line}` ;
    path += `&column=${robot.column}` ;
    path += `&state=${robot.state}` ;
    path += `&move=${move}` ;
    console.log(path) ;
    xmlHttp.open("GET", path, true);
    xmlHttp.send(null);
  }

  get_board() ;

  document.getElementById("forward_1").addEventListener('click', (e) => {
    move_robot(robot_moves.FORWARD_1) ;
  }) ;

  document.getElementById("forward_2").addEventListener('click', (e) => {
    move_robot(robot_moves.FORWARD_2) ;
  }) ;

  document.getElementById("forward_3").addEventListener('click', (e) => {
    move_robot(robot_moves.FORWARD_3) ;
  }) ;

  document.getElementById("backward_1").addEventListener('click', (e) => {
    move_robot(robot_moves.BACKWARD_1) ;
  }) ;

  document.getElementById("turn_left").addEventListener('click', (e) => {
    move_robot(robot_moves.TURN_LEFT) ;
  }) ;

  document.getElementById("turn_right").addEventListener('click', (e) => {
    move_robot(robot_moves.TURN_RIGHT) ;
  }) ;

  document.getElementById("u_turn").addEventListener('click', (e) => {
    move_robot(robot_moves.U_TURN) ;
  }) ;
})
