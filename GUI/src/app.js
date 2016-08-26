import React from 'react';
import ReactDOM from 'react-dom';
import injectTapEventPlugin from 'react-tap-event-plugin';
import MuiThemeProvider from 'material-ui/styles/MuiThemeProvider';
import Avatar from 'material-ui/Avatar';
import FontIcon from 'material-ui/FontIcon';
import TextField from 'material-ui/TextField';
import FlatButton from 'material-ui/FlatButton';
import IconButton from 'material-ui/IconButton';

import Undo from 'material-ui/svg-icons/content/undo';
import Redo from 'material-ui/svg-icons/content/redo';
import PlayArrow from 'material-ui/svg-icons/av/play-arrow';
import Pause from 'material-ui/svg-icons/av/pause';

import {
grey500 as neutralColor,
red500 as errorColor,
blue200 as lightColor,
blue500 as darkColor,
blue700 as darkerColor,
} from 'material-ui/styles/colors';

import request from 'superagent'

function requestSolution(array, callback){
    request.post('/solve').
          send(array).
          set('Accept', 'application/json').
          end(callback)
}

injectTapEventPlugin();

class NextArrow extends React.Component {
    render() {
        return <p style={{margin: 5, display: 'inline'}}>＞</p>
    }
}

class InputView extends React.Component {
    constructor(props){
        super(props)
        this.onNewClockSubmitted = this.onNewClockSubmitted.bind(this)
        this.state = {
            clockText: "",
        }
    }

    onNewClockSubmitted(){
        const exp = new RegExp("/^\s*\d[\d\s]*$/")
        const validChars = "1234567890 "
        const newClockText = this.state.clockText
        let valid = true
        for(let i = 0; i < newClockText.length; i++){
            if(!validChars.includes(newClockText.charAt(i)))
                valid = false
        }

        if(valid){
            this.props.onNewClock(newClockText.split(" "))
        }
    }

    render(){
        return(
            <div style={{position: 'relative', textAlign: 'center', margin: 20}}>
              <TextField onChange={(e) => this.setState({clockText: e.target.value.trim()})}
              style={{position:'relative'}} hintText={"Clock face values"} name={"clockInput"}/>
              <FlatButton label="solve" primary={true} onClick={() => this.onNewClockSubmitted()}/>
            </div>
          )
    }
}

class ClockView extends React.Component {
    render() {
        const avatarStyle = {margin: 5}
        return (
          <div style={{textAlign:'center'}}>
            {this.props.clock.map((clockItem, i) => {
                let color = neutralColor
                if(this.props.currentPosition === i)
                    color = darkerColor
                else if(this.props.lastPosition === i)
                    color = darkColor
                else if(this.props.errorPosition === i)
                    color = errorColor
                else if(this.props.visitedPositions.includes(i))
                    color = lightColor
                if(i === 0)
                    return (
                      <Avatar key={i} backgroundColor={color} style={avatarStyle}>{clockItem}</Avatar>
                    )
                else
                return (
                  <div style={{display: 'inline'}} key={i}>
                  <NextArrow />
                  <Avatar backgroundColor={color} style={avatarStyle}>{clockItem}</Avatar>
                  </div>
                )
            })}
          </div>
        )
    }
}

class StateNavigation extends React.Component {
    render(){
        const buttonsDistance = 120
        const iconStyle = {width: 36, height: 36}
        const defStyle = {width: 72, height: 72, padding: 16}

        let animIcon = <PlayArrow />
        if(this.props.isPlaying)
            animIcon = <Pause />
        return (
          <div>
            <h2 style={{textAlign:'center'}}>State Navigation</h2>
            <ClockView clock={this.props.currentState} visitedPositions={[]}/>
            <br />
            <p style={{textAlign: 'center', marginBottom: 0}}>{this.props.footerMsg}</p>
            <div style={{position: 'relative', textAlign: 'center' }}>
              <IconButton iconStyle={iconStyle} style={defStyle}
                disabled={this.props.isPlaying} onTouchTap={() => this.props.undo()}>
                <Undo />
              </IconButton>
              <IconButton iconStyle={iconStyle}
              style={{ ...defStyle, marginLeft: buttonsDistance, marginRight: buttonsDistance}}
                onTouchTap={() => this.props.play()}>
                { animIcon }
              </IconButton>
              <IconButton iconStyle={iconStyle} style={defStyle}
                disabled={this.props.isPlaying} onTouchTap={() => this.props.redo()}>
                <Redo />
              </IconButton>
            </div>
          </div>
        )
    }
}

class AppContainer extends React.Component {
    constructor(props){
        super(props)
        this.state = {
            clock: [],
            statesList: [],
            currentIndex: 0,
            isPlaying: false,
        }
        this.undo = this.undo.bind(this)
        this.redo = this.redo.bind(this)
        this.play = this.play.bind(this)
    }

    undo(){
        const index = this.state.currentIndex
        if(!this.state.isPlaying)
            this.setState({currentIndex: Math.max(0, index - 1)})
    }

    redo(){
        const index = this.state.currentIndex
        if(!this.state.isPlaying)
            this.setState({currentIndex: Math.min(this.state.statesList.length - 1, index + 1)})
    }

    play(){
        if(!this.state.isPlaying){
            this.setState({currentIndex: 0, isPlaying: true})
            const newFrame = () => {
                setTimeout(() => {
                    const index = this.state.currentIndex
                    this.setState({currentIndex: index + 1})
                    if(this.state.isPlaying && index < this.state.statesList.length - 2){
                        newFrame()
                    } else if(this.state.isPlaying) {
                        this.setState({isPlaying: false})
                    }
                }, 1500)
            }
            newFrame()
        } else {
            this.setState({isPlaying: false})
        }
    }

    render(){
        let currentStateViewer = <div />
        let currentPosition = -1
        let lastPosition = -1
        let errorPosition = -1
        let msg = ""
        let visitedPositions = []
        if(this.state.statesList.length > 0){
            const currentStateList = this.state.statesList[this.state.currentIndex]
            const msg =`${this.state.currentIndex + 1}/${this.state.statesList.length}`
            visitedPositions = currentStateList
            currentStateViewer = <StateNavigation footerMsg={msg} play={this.play}
            currentState={currentStateList} undo={this.undo} redo={this.redo}
            isPlaying={this.state.isPlaying} />
            currentPosition = currentStateList[currentStateList.length - 1]

            if(currentStateList.length > 1){
                lastPosition = currentStateList[currentStateList.length - 2]
            }

            if(this.state.currentIndex > 0){
                const prevState = this.state.statesList[this.state.currentIndex - 1]
                if(prevState.length > currentStateList.length)
                    errorPosition = prevState[prevState.length - 1]
            }

        } else if(this.state.clock.length > 0){//got a clock, but no solutions
            currentStateViewer = <p style={{textAlign:'center'}}>No solutions found</p>

        }
        return (
          <div>
            <h1 style={{textAlign:'center'}}>Hands of Fate Puzzle Solver</h1>
            <InputView onNewClock={(newClock) => requestSolution(newClock,
              (req, res) => {
                  const response = JSON.parse(res.text)
                  this.setState({clock: newClock, statesList: response, currentIndex: 0})
              }
            )}/>
            <ClockView clock={this.state.clock} visitedPositions={visitedPositions}
            lastPosition={lastPosition} currentPosition={currentPosition}
            errorPosition={errorPosition}/>
            <br /><br />
            { currentStateViewer }
          </div>
        )
    }
}
let currentClock = []
const App = () => (
  <MuiThemeProvider>
      <AppContainer />
  </MuiThemeProvider>
);

ReactDOM.render(<App />,
		document.getElementById('root'));
