-- Gkyl ------------------------------------------------------------------------
--
-- Species base object
--
--    _______     ___
-- + 6 @ |||| # P ||| +
--------------------------------------------------------------------------------

local Proto = require "Lib.Proto"

-- empty shell species base class
local SpeciesBase = Proto()

-- functions that must be defined by subclasses
function SpeciesBase:init(tbl) end
function SpeciesBase:fullInit(appTbl) end
function SpeciesBase:setName(nm) end
function SpeciesBase:setIoMethod(ioMethod) end
function SpeciesBase:createGrid(cLo, cUp, cCells, cDecompCuts, cPeriodicDirs, cMap) end
function SpeciesBase:setConfBasis(basis) end
function SpeciesBase:createBasis() end
function SpeciesBase:setConfGrid(grid) end
function SpeciesBase:alloc(nRkDup) end
function SpeciesBase:setCfl(cfl) end
function SpeciesBase:setDtGlobal(dtGlobal) end
function SpeciesBase:getNdim() return 1 end
function SpeciesBase:createSolver() end
function SpeciesBase:createDiagnostics() end
function SpeciesBase:rkStepperFields() return { nil } end
function SpeciesBase:suggestDt() end
function SpeciesBase:clearCFL() end
function SpeciesBase:clearMomentFlags(species) end
function SpeciesBase:initDist() end
function SpeciesBase:initCrossSpeciesCoupling() end
function SpeciesBase:calcCouplingMoments() end
function SpeciesBase:write(tm) end
function SpeciesBase:writeRestart(tm) end
function SpeciesBase:readRestart() return 0.0 end
function SpeciesBase:advance(tCurr, species, emIn, inIdx, outIdx) return true, GKYL_MAX_DOUBLE end
function SpeciesBase:updateInDirection(dir, tCurr, dt, fIn, fOut) return true, GKYL_MAX_DOUBLE end
function SpeciesBase:applyBcIdx(tCurr, idx) end
function SpeciesBase:applyBc(tCurr, fld) end
function SpeciesBase:totalSolverTime() return 0.0 end
function SpeciesBase:momCalcTime() return 0.0 end
function SpeciesBase:intMomCalcTime() return 0.0 end
function SpeciesBase:totalBcTime() return 0.0 end
function SpeciesBase:getCharge() return 0.0 end
function SpeciesBase:getMass() return 1.0 end
function SpeciesBase:copyRk(outIdx, aIdx) end
function SpeciesBase:combineRk() end

return SpeciesBase

