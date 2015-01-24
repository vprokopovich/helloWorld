var requestIds = [];
var requests = new Object();
var msgPool = null;
var state = null;

$(document).ready(function() {
    msgPool = new Firebase('https://heater-contol.firebaseio.com/msg-pool/');
    state = new Firebase('https://heater-contol.firebaseio.com/state/');

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
    requests[oldChildSnapshot.key()] = null;
    $("div#lblRequests").html(JSON.stringify(requests));
}

function handleMsgRequest(childSnapshot, prevChildName)
{
    //$("body").append("<div>"+JSON.stringify(childSnapshot.key())+"___" + prevChildName+"</div>");
    requests[childSnapshot.key()] = childSnapshot.val();
    $("div#lblRequests").html(JSON.stringify(requests));
}

function updateView(status, temperature, targetTemperature, targetTime, timerActivated)
{
    $("div#lblStatus").html(status);
    $("div#lblTemp").html(temperature);
    $("input#txtTargetTemp").val(targetTemperature);
    $("input#txtTargetTime").val(targetTime);
}

function onTargetTemperatureChange()
{
    var newTemperature = $("input#txtTargetTemp").val();
    var newMessageRef = msgPool.push({'action': 'targetTemp', 'value': newTemperature});
    var path = newMessageRef.toString();
    requestIds.push(path);
}