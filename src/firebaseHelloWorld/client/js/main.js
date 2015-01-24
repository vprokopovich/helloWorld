var requests = new Object();
var msgPool = null;
var state = null;

$(document).ready(function()
{
    msgPool = new Firebase('https://heater-control.firebaseio.com/msg-pool/');
    state   = new Firebase('https://heater-control.firebaseio.com/state/');

    state.on('value', handleStateChanged);
    msgPool.on('child_removed', handleMsgResponse);
    msgPool.on('child_added', handleMsgRequest);

    $("input#txtTargetTemp").change(onTargetTemperatureChange);
});

function handleStateChanged(snapshot)
{
    if (null == snapshot) return;

    var status = snapshot.val();
    updateView(status.status, status.temp, status.targetTemp, status.targetTime, status.timerActivated);
}

function handleMsgResponse(oldChildSnapshot)
{
    delete requests[oldChildSnapshot.key()];
    updateViewProcessingRequests();
}

function handleMsgRequest(childSnapshot, prevChildName)
{
    requests[childSnapshot.key()] = childSnapshot.val();
    updateViewProcessingRequests();
}

function updateView(status, temperature, targetTemperature, targetTime, timerActivated)
{
    $("div#lblStatus").html(status);
    $("div#lblTemp").html(temperature);
    $("input#txtTargetTemp").val(targetTemperature);
    $("input#txtTargetTime").val(targetTime);
}

function updateViewProcessingRequests()
{
    if (false == isEmpty(requests))
    {
        $("div#lblRequestStatus").html("Processing request");
        $("div#lblRequests").html(JSON.stringify(requests));
    }
    else
    {
        $("div#lblRequestStatus").html("All requests processed");
        $("div#lblRequests").html("");
    }    
}

function onTargetTemperatureChange()
{
    var newTemperature = $("input#txtTargetTemp").val();
    msgPool.push({'action': 'targetTemp', 'value': newTemperature});
}

function isEmpty(obj)
{
    return Object.keys(obj).length === 0;
}