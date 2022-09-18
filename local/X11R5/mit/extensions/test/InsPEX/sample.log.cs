Below is the result of an InsPEX run on the released version
of the PEX libraries and server, using client-side storage
on a Sun 3/260. A server-side storage run is in the file 
sample.log.ss in the same directory.

The failures below consist of the three described at the top of sample.log.ss
(wsxf5, dcue2, and nurbss6), plus most of the ISS (incremental
structure search) and picking tests, since this functionality is not
implemented for client-side storage.  Also, the test ptrlabel2 causes
the correct PHIGS error message, rather than the less useful X error
reported when server-side storage is used.

------------------- beginning of test log ---------------------
The InsPEX Test Suite 5.2
Run started on Thu Feb 14 09:33:10 PST 1991
Running on client machine derkins
Using default display, unix:0
Test results going into log file /home/derkins/inspex/ilog02.14.0933
server is responding - xdpyinfo output in display_info
I_CLIENT_SIDE is set - client side storage will be used
emptying dirs bin, lib, tmp under INSPEXDEST
emptying directory include under INSPEXDEST
PEX include directory:        /home/derkins/pex/include
PEX lib directory:            /home/derkins/pex/lib
X include directory:          /home/derkins/pex/include
X lib directory:              /home/derkins/pex/lib
InsPEX home directory:        /home/goldbach/jamison/inspex
InsPEX destination directory: /home/derkins/inspex
Image reference directory:    /usr/graphics/src/inspex/refimages
make CPPFLAGS='-DNEWT' PEXINCDIR=/home/derkins/pex/include PEXLIBDIR=/home/derkins/pex/lib XINCDIR=/home/derkins/pex/include XLIBDIR=/home/derkins/pex/lib I_CFLAGS= I_LDFLAGS= pexint
-------- Starting test area statectl --------
systemst: PASSED: system operating state
wsst1: PASSED: X drawable workstation operating state
wsst2: PASSED: X tool workstation operating state
structst: PASSED: structure operating state
archivest: PASSED: archive operating state
-------- Starting test area utils --------
translate: PASSED: translation utilities
scale: PASSED: scale utilities
rotate: PASSED: rotate utilities
compmtx: PASSED: compose matrix utilities
buildtran: PASSED: build transformation utilities
comptran: PASSED: compose transformation utilities
tranpt: PASSED: tranform point utilities
evalori: PASSED: eval orientation matrix utilities
evalmap: PASSED: eval mapping matrix utilities
-------- Starting test area rep --------
edgerep: PASSED: set and inquire edge representation
linerep: PASSED: set and inquire polyline representation
markerrep: PASSED: set and inquire polymarker representation
colourrep: PASSED: set and inquire colour representation
textrep: PASSED: set and inquire text representation
viewrep: PASSED: set and inquire view representation
patrep: PASSED: set and inquire pattern representation
interrep: PASSED: set and inquire interior representation
dcuerep: PASSED: set and inquire depth cue representation
lightrep: PASSED: set and inquire light source representation
-------- Starting test area xform --------
wsxf1: PASSED: set and inquire workstation transformation
wsxf2: PASSED: 2D/3D workstation transformation consistency
wsxf3: PASSED: rendering with ws transformation using square ws
wsxf4: PASSED: rendering with ws transformation using non-square ws
wsxf5: failed: 3D line crossing front edge, pixel not expected
wsxf5: failed: 3D line crossing back edge, pixel not expected
wsxf5: FAILED: workstation clipping
viewxf1: PASSED: view orientation transformation
viewxf2: PASSED: view mapping transformation
viewxf3: PASSED: view clipping
viewxf4: PASSED: view index attribute inheritance
viewxf5: PASSED: view front and back plane clipping
modelxf1: PASSED: local modelling transformation
modelxf2: PASSED: composite modelling transformation
modelxf3: PASSED: global transformation attribute inheritance
modelxf4: PASSED: modelling clipping indicator attribute inheritance
modelxf5: PASSED: modelling clipping indicator attribute inheritance
modelxf6: PASSED: modelling clipping volume
modelxf7: PASSED: modelling clipping volume attribute inheritance
modelxf8: PASSED: restore modelling clipping volume
modelxf9: PASSED: transformtion of half-spaces
primxf1: PASSED: Test transformation with different primitives
primxf2: PASSED: view clipping with different primitives
primxf3: PASSED: modelling clipping with different primitives
-------- Starting test area dispctl --------
redrawstr: PASSED: redraw all structures with post and unpost structure
updatews: PASSED: update workstation with structure content modification
dispupst1: PASSED: set and inquire display update state
dispupst2: PASSED: display update with ws xform modification (WAIT/NIVE,UQUM,UWOR)
dispupst3: PASSED: display update with ws xform mod (ASAP,BNIG,BNIL/NIVE,UQUM,UWOR)
dccolrep: PASSED: display update with colour representation modification
dcdelstr: PASSED: display update with delete structure
dclinerep: PASSED: display update with polyline bundle representation modification
dcrefmod: PASSED: display update with reference modification
dcviewrep: PASSED: display update with view representation modification 
-------- Starting test area fillarea --------
fa1: PASSED: fill area geometry and individual interior attributes
fa2: PASSED: adjacent fill areas and interior colour
fa3: PASSED: fill area bundle attributes
fa4: PASSED: fill area - lighting attributes
fas1: PASSED: fill area set geometry and individual interior attributes
fas2: PASSED: fill area set geometry with n-set, n>1
fas3: PASSED: adjacent fill area set edges and edge colours
fas4: PASSED: combinations of edge type, edge colour and interior style
fas5: PASSED: combinations of edge type end edge width
fas6: PASSED: fill area set bundle attributes
fas7: PASSED: fill area set attributes inheritance
fas8: PASSED: fill area set - lighting attributes
-------- Starting test area search --------
elemsrch1: PASSED: element search
elemsrch2: PASSED: element search
elemsrch3: PASSED: element search
elemsrch4: PASSED: element search on empty structure
-------- Starting test area text --------
tx1: PASSED: text geometry
tx2: PASSED: text colour index
tx3: PASSED: text path
tx4: PASSED: char up vector
tx5: PASSED: char expansion
tx6: PASSED: char spacing
tx7: PASSED: char height
tx8: PASSED: text alignment
tx9: PASSED: text fonts and precision
tx10: PASSED: text bundle attributes
tx11: PASSED: text attributes inheritance
atx1: PASSED: annotation text geometry and style
atx2: PASSED: annotation text colour index
atx3: PASSED: annotation text path
atx4: PASSED: annotation text char up vector
atx5: PASSED: annotation text char expansion factor
atx6: PASSED: annotation text char spacing
atx7: PASSED: annotation char height
atx8: PASSED: annotation text alignment
atx9: PASSED: annotation text font and precision
atx10: PASSED: annotation text bundle attributes
atx11: PASSED: annotation text attributes inheritance
-------- Starting test area strcon --------
copyall1.pi: PASSED: test COPY ALL ELEMENTS FROM STRUCTURE
delelem1: PASSED: DELETE ELEMENTS function on size 0 and 1 structures
delelem2: PASSED: DELETE ELEMENTS function on multi-element structures
dellabel1: PASSED: DELETE ELEMENT BETWEEN LABELS
delrange1: PASSED: DELETE ELEMENT RANGE w/ ptr1 <,>,= ptr2
delrange2: PASSED: DELETE ELEMENT RANGE at ends of structure
editmode1: PASSED: Setting and inquiry of edit mode
editmode2: PASSED: Editing structures in REPLACE mode with elem ptr 0
editmode3: PASSED: Editing structures with REPLACE mode
editmode4: PASSED: Editing structures with INSERT mode
elemptr1: PASSED: basic set & inquire of element pointer
emptystr1: PASSED: test function EMPTY STRUCTURE
offset1: PASSED: test OFFSET ELEMENT POINTER
openstr1.pi: PASSED: test INQUIRE OPEN STRUCTURE
openstr2.pi: PASSED: test INQUIRE OPEN STRUCTURE w/ open WS
ptrlabel1: PASSED: test SET ELEMENT POINTER AT LABEL
PHIGS error 205 in SET ELEMENT POINTER AT LABEL: Ignoring function, the label
does not exist in the open structure between the element pointer and the end of
the structure
ptrlabel2: PASSED: error conditions (expected) for SET ELEMENT POINTER AT LABEL
strstat1: PASSED: test INQUIRE STRUCTURE STATUS
copyall2: PASSED: test COPY ALL ELEMENTS FROM STRUCTURE w/ variable length data

elemcon9: PASSED: inquiring element type, size, content (1 2 3 4 5 6)
elemcon9: PASSED: inquiring element type, size, content (7 8)
elemcon9: PASSED: inquiring element type, size, content (9)
elemcon9: PASSED: inquiring element type, size, content (10 11)
elemcon9: PASSED: inquiring element type, size, content (12 13 14 15 16 17 18 19 20)
elemcon9: PASSED: inquiring element type, size, content (21)
elemcon9: PASSED: inquiring element type, size, content (22 23 24 25 26 27 28 29 30)
elemcon9: PASSED: inquiring element type, size, content (31 32 33 34 35 36 37 38 39 40)
elemcon9: PASSED: inquiring element type, size, content (41 42)
elemcon9: PASSED: inquiring element type, size, content (43 44)
elemcon9: PASSED: inquiring element type, size, content (45 46 47 48 49 50)
elemcon9: PASSED: inquiring element type, size, content (51 52 53 54 55 56 57 59 60)
elemcon9: PASSED: inquiring element type, size, content (58)
elemcon9: PASSED: inquiring element type, size, content (61 62 63 64 65 66 67 68)
elemcon9: PASSED: inquiring element type, size, content (69 70 71 72 73 74 75 76 77 78 79 80)
elemcon9: PASSED: inquiring element type, size, content (81)
elemcon9: PASSED: inquiring element type, size, content (82 83 84)
elemcon9: PASSED: inquiring element type, size, content (85 86)
elemcon9: PASSED: inquiring element type, size, content (87)
elemcon9: PASSED: inquiring element type, size, content (88)
elemcon9: PASSED: inquiring element type, size, content (89 90 91 92)
elemcon9: PASSED: inquiring element type, size, content (93)
-------- Starting test area strman --------
delallst1.pi: PASSED: del_all_structs on non-existent and simple structs
delallst2.pi: PASSED: del_all_structs on multi-level structs
delstnet1: PASSED: delete structure network on non-existent structure
delstnet2: PASSED: delete structure network on simple structures
delstr1: PASSED: delete structure on non-existent and simple structures
delstr2: PASSED: delete structure on multi-level structures
delstr3: PASSED: deleting open structures
delstr4: PASSED: deleting posted structures
delstr5: PASSED: delete structures referenced in open structure
poststr1: PASSED: post non-existent, open, and closed structures.
poststr2: PASSED: post overlapping structures of different priority
poststr3: PASSED: post structures differently on different workstations
-------- Starting test area poly --------
polyline1: PASSED: test POLYLINE with various numbers of points
polyline2: PASSED: POLYLINE with combinations of width & line type
polyline3: PASSED: POLYLINE using colors 0-7
polyline4: PASSED: POLYLINE with combinations of width & line type
pl_inher: PASSED: polyline attributes inheritance
polymark1: PASSED: test polymarker with various numbers of points
polymark2: PASSED: polymarkers with combinations of size & type
polymark3: PASSED: centering of polymarkers
polymark4: PASSED: interference between marker and line attrs
pm_inher: PASSED: polymarker attributes inheritance
-------- Starting test area plinedata --------
pldata1: PASSED: POLYLINE_SET3_DATA with simple geometries, widths
pldata2: PASSED: POLYLINE_SET3_DATA combinations of width & line type
pldata3: PASSED: polyline set3 w/data, with index color
pldata4: PASSED: polyline_set3_data with no data
pld_inher: PASSED: polyline_set3_data attribute inheritance
-------- Starting test area archive --------
confres: PASSED: set and inquire conflict resolution flags
archive: PASSED: simple archive operations
archstr: PASSED: archive structure with different conflict resolutions
archnet: PASSED: archive structure network with different conflict resolutions
archall: PASSED: archive all structures with different conflict resolutions
retrieve: PASSED: simple retrieve operations
retrstr: PASSED: retrieve structure with different conflict resolutions
retrnet: PASSED: retrieve structure network with different conflict resolutions
retrall: PASSED: retrieve all structures with different conflict resolutions
deletear: PASSED: simple delete structure from archive operations
delstrar: PASSED: delete structure from archive
delnetar: PASSED: delete structure network from archive
delallar: PASSED: delete all structures from archive
specar1: PASSED: special cases arhive, retrieve, and delete all structures
specar2: PASSED: special cases archive operation on open structure
specar3: PASSED: special cases archive using multiple archive files
specar4: PASSED: special cases archive operation
inqcfnet: PASSED: inquire conflicting structures in network
inqallcf: PASSED: inquire all conflicting structures
retrances: PASSED: retrieve paths to ancestors
retrdesc: PASSED: retrieve paths to descendants
-------- Starting test area face --------
cull1: PASSED: face culling
cull2: PASSED: Test face culling with different primitives
-------- Starting test area dcue --------
dcue1: PASSED: depth cue mode, reference planes and scaling
dcue2: failed - no reference image for dcue2 (saving current image)
dcue2: FAILED: Test depth cuing with different primitives
-------- Starting test area nurbs --------
nurbsc1: PASSED: nurb curve geometry and line attributes
nurbsc2: PASSED: nurbs curve approximation criteria
nurbsc3: PASSED: nurbs curve bundle attributes
nurbss1: PASSED: nurbs surface geometry with trimming curves
nurbss2: PASSED: nurbs surface with edge and interior attributes
nurbss3: PASSED: nurbs surface with bundled edge and reflectance attributes
nurbss4: PASSED: nurbs surface with reflectance attributes
nurbss5: PASSED: nurbs surface approximation criteria
nurbss6: failed - no reference image for nurbss6 (saving current image)
nurbss6: FAILED: nurbs parametric surface
-------- Starting test area triquad --------
ts1: PASSED: triangle strip with data - geometry and facet/vertex colour
ts2: PASSED: triangle strip with data - interior and edge attributes
ts3: PASSED: triangle strip with data - bundled interior, edge and reflectance attributes
ts4: PASSED: triangle strip with data - geometry and lighting attributes
ts5: PASSED: triangle strip with data - interior and edge attributes inheritance
ts6: PASSED: triangle strip with data - reflectance characteristic and properties attributes inheritance
qm1: PASSED: quad mesh with data geometry and facet/vertex colour
qm2: PASSED: quad mesh with data - interior and edge attributes
qm3: PASSED: quad mesh with data - bundled interior, edge and reflectance attributes
qm4: PASSED: quad mesh with data - geometry and lighting attributes
faswd1: PASSED: fill area set with data - geometry and facet/vertex colour
faswd2: PASSED: fill area set with data with data - interior and edge attributes
faswd3: PASSED: fill area set with data with data - bundled interior, edge and reflectance attributes
faswd4: PASSED: fill area with data with data - geometry and lighting attributes
sofas1: PASSED: set of fill area set with data - geometry and facet/vertex colour
sofas2: PASSED: set of fill area set with data with data - interior and edge attributes
sofas3: PASSED: set of fill area set with data with data - bundled interior, edge and reflectance attributes
sofas4: PASSED: set of fill area with data with data - geometry and lighting attributes
-------- Starting test area light --------
light1: PASSED: ambient light - ambient coefficient
light2: PASSED: positional light - diffuse coefficient and attenuation
light3: PASSED: positional light - light source positions
light4: PASSED: directional light - diffuse coefficient and direction
light5: PASSED: multiple light sources
-------- Starting test area iss --------
iss1: ERROR: -500 in pincr_spa_search
iss1: failed: found path != expected for start path = (0,0)
iss1: ERROR: -500 in pincr_spa_search
iss1: failed: found path != expected for start path = (0,1)
iss1: ERROR: -500 in pincr_spa_search
iss1: Exiting, too many failures (5).
iss1: FAILED: incremental spatial search - incremental properties
iss2: ERROR: -500 in pincr_spa_search
iss2: failed: found path != expected for iss without ceiling
iss2: ERROR: -500 in pincr_spa_search
iss2: FAILED: incremental spatial search - with/without ceiling
iss3: ERROR: -500 in pincr_spa_search
iss3: failed: found path != expected for start path = (0,1)
iss3: ERROR: -500 in pincr_spa_search
iss3: failed: found path != expected for start path = (0,3)
iss3: ERROR: -500 in pincr_spa_search
iss3: Exiting, too many failures (5).
iss3: FAILED: incremental spatial search - search filter
iss4: ERROR: -500 in pincr_spa_search
iss4: failed: found path != expected, 2D case
iss4: ERROR: -500 in pincr_spa_search
iss4: failed: found path != expected, 2D case
iss4: ERROR: -500 in pincr_spa_search
iss4: Exiting, too many failures (5).
iss4: FAILED: incremental spatial search(3) - spatial properties
iss5: ERROR: -500 in pincr_spa_search
iss5: ERROR: -500 in pincr_spa_search
iss5: failed: found path != expected with non-clipped point as reference
iss5: FAILED: incremental spatial search(3) - with model clipping
iss6: ERROR: -500 in pincr_spa_search
iss6: ERROR: -500 in pincr_spa_search
iss6: annotation text, search dist=1.0, found path != expected
iss6: ERROR: -500 in pincr_spa_search
iss6: ERROR: -500 in pincr_spa_search
iss6: Exiting, too many failures (5).
iss6: FAILED: incremental spatial search with different primitives
-------- Starting test area error --------
errhandle1: PASSED: test error output file and error mode
errhandle2: PASSED: test user installed error handler
-------- Starting test area pdtwdt --------
pdt: PASSED: verify data from PHIGS description table
wdt1: PASSED: "colour X tool" workstation facilities inquiry
wdt2: PASSED: "colour X tool" ws's pred rep & list of indices inquiries
wdt3: PASSED: "colour X tool" ws miscellaneous inquires
wdt4: PASSED: "colour X tool" workstation's default input data inquiries
wdt5: PASSED: "colour X tool" PHIGS+ workstation facilities inquiry
wdt6: PASSED: "colour X tool" PHIGS+ ws's pred rep & list of indices inquiries
-------- Starting test area filter --------
highl: PASSED: highlight filter
invis: PASSED: invisibility filter
pick: failed: pick filter incl(1),excl(), current nameset(1,2,3)
pick: failed: pick filter incl(1,2),excl(3), current nameset(1,2)
pick: failed: pick filter incl(1,2),excl(3), current nameset(1)
pick: FAILED: pick filter
-------- Starting test area input --------
loc1: PASSED: initialize locator
loc2: PASSED: set locator mode
loc3: PASSED: locator in SAMPLE mode
loc4: PASSED: locator in REQUEST mode
loc5: PASSED: locator in EVENT mode
event1: PASSED: await event with multiple ws
event2: PASSED: await event with different timeout values
event3: PASSED: await event with sucessive events
event4: PASSED: flush events
event5: PASSED: simultaneous events
event6: PASSED: inquire input overflow
viewpri1: PASSED: setting view transform input priority
viewpri2: PASSED: view transform input priority with locator
val1: PASSED: initialize valuator
val2: PASSED: set valuator mode
stroke1: PASSED: initialize and sample stroke
stroke2: PASSED: set stroke mode
pick1: PASSED: initialize pick
pick2: PASSED: set pick mode
pick3: failed: pick status = 1 expected PIN_STATUS_OK
pick3: FAILED: pick in SAMPLE mode
pick4: failed: pick status = 1 expected PIN_STATUS_OK
pick4: FAILED: pick in REQUEST mode
pick5: failed: pick status = 1 expected PIN_STATUS_OK
pick5: FAILED: pick in EVENT mode
pick6: failed: pick status = 1 expected PIN_STATUS_OK
pick6: failed: pick status = 1 expected PIN_STATUS_OK
pick6: failed: pick status = 1 expected PIN_STATUS_OK
pick6: failed: pick status = 1 expected PIN_STATUS_OK
pick6: FAILED: picking structure network and pick id inheritance
pick7: failed: pick status = 1 expected PIN_STATUS_OK
pick7: FAILED: picking clipped primitive
pick8: failed: pick status = 1 expected PIN_STATUS_OK
pick8: FAILED: picking modelling transformed primitive
pick9: failed: visible primitive is not being picked
pick9: FAILED: picking with invisibility filter
pick10: failed: annotation text is not being picked
pick10: failed: fill area is not being picked
pick10: failed: fill area set is not being picked
pick10: failed: fill area set with data is not being picked
pick10: failed: nurb curve is not being picked
pick10: Exiting, too many failures (5).
pick10: FAILED: Test picking with different primitives
string1: PASSED: initialize string
string2: PASSED: set string mode
choice1: PASSED: initialize choice
choice2: PASSED: set choice mode
InsPEX run completed on  Thu Feb 14 10:37:52 PST 1991
