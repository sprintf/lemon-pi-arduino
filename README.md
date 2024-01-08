# lemon-pi-arduino
the code for the lemon-pi arduino unit

## Commands
`up` : raise the drag reduction system, reducing drag
`down` : lower the drag reduction system, increasing downforce

## Requirements
- If we receive an 'up' while already processing an 'up' we ignore the second request
- If we receive a 'down' request while performing an 'up' we immediately stop the 'up'
and perform a 'down'
- Vice-versa to all the above
