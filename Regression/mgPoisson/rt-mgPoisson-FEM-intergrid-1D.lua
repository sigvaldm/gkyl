-- Gkyl ------------------------------------------------------------------------
--
-- Test 1D FEM inter-grid operators in the MGpoisson updater.
--
--    _______     ___
-- + 6 @ |||| # P ||| +
--------------------------------------------------------------------------------

local Grid       = require "Grid"
local DataStruct = require "DataStruct"
local Basis      = require "Basis"
local Updater    = require "Updater"

-- .......................... User inputs ............................ --

local pOrder    = 1                   -- Polynomial order.
local basisName = "Ser"               -- Type of polynomial basis.
 
local numCells  = {{8}, {16}}         -- Number of cells of the two grids.
local lower     = {0.0}               -- Lower boundary of the domain.
local upper     = {1.0}               -- Upper boundary of the domain.

-- .................. end of user inputs (MAYBE) .................... --


local tests = {}
-- Lower and Upper homogeneous Dirichlet BCs.
tests[1] = {}
tests[1]["a"]            = 2.0
tests[1]["c"]            = {(tests[1]["a"]/12.0-0.5), 0.0}
tests[1]["mu"]           = 0.0
tests[1]["bcStr"]        = "LxHomoDUxHomoD"
tests[1]["periodicDirs"] = {}
tests[1]["bcLower"]      = { {T="D", V=0.0} }
tests[1]["bcUpper"]      = { {T="D", V=0.0} }
-- Lower homogeneous Neumann, upper homogeneous Dirichlet.
tests[2] = {}
tests[2]["a"]            = 5.0
tests[2]["c"]            = {0.0, (tests[2]["a"]/12.0-0.5)}
tests[2]["mu"]           = 0.0
tests[2]["bcStr"]        = "LxHomoNUxHomoD"
tests[2]["periodicDirs"] = {}
tests[2]["bcLower"]      = { {T="N", V=0.0} }
tests[2]["bcUpper"]      = { {T="D", V=0.0} }
-- Lower homogeneous Dirichlet, upper homogeneous Neumann.
tests[3] = {}
tests[3]["a"]            = 5.0
tests[3]["c"]            = {0.0, (tests[3]["a"]/12.0-0.5)}
tests[3]["mu"]           = 1.0
tests[3]["bcStr"]        = "LxHomoDUxHomoN"
tests[3]["periodicDirs"] = {}
tests[3]["bcLower"]      = { {T="D", V=0.0} }
tests[3]["bcUpper"]      = { {T="N", V=0.0} }
-- Periodic.
tests[4] = {}
tests[4]["a"]            = {1, 2, 5}
tests[4]["c"]            = {1, 2, 5}
tests[4]["mu"]           = 0.0
tests[4]["bcStr"]        = "xPeriodic"
tests[4]["periodicDirs"] = {1}
tests[4]["bcLower"]      = { {T="P", V=0.0} }
tests[4]["bcUpper"]      = { {T="P", V=0.0} }

-- Function to transfer between grids.
local function testFunction(xn, aIn, cIn, muIn, pDirs)
   local x = xn[1]
   if #pDirs < 1 then
      return ((x-muIn)^2)/2.0-aIn*((x-muIn)^4)/12.0+cIn[1]*x+cIn[2]
   else
      local am         = aIn
      local bm         = cIn
      local cosT, sinT = 0.0, 0.0
      local f          = 0.0
      for m = 0,2 do
         cosT = am[m+1]*math.cos(2.*math.pi*m*x)
         sinT = bm[m+1]*math.sin(2.*math.pi*m*x)
         f  = f + (cosT+sinT)
      end
      return f
   end
end

local function createGrid(lo, up, nCells, pDirs)
   local gridOut = Grid.RectCart {
      lower        = lo,
      upper        = up,
      cells        = nCells,
      periodicDirs = pDirs,
   }
   return gridOut
end

local function createBasis(dim, pOrder, bKind)
   local basis
   if (bKind=="Ser") then
      basis = Basis.CartModalSerendipity { ndim = dim, polyOrder = pOrder }
   elseif (bKind=="Max") then
      basis = Basis.CartModalMaxOrder { ndim = dim, polyOrder = pOrder }
   elseif (bKind=="Tensor") then
      basis = Basis.CartModalTensor { ndim = dim, polyOrder = pOrder }
   else
      assert(false,"Invalid basis")
   end
   return basis
end

local function createField(grid, basis, vComp)
   vComp = vComp or 1
   local fld = DataStruct.Field {
      onGrid        = grid,
      numComponents = basis:numBasis()*vComp,
      ghost         = {1, 1},
      metaData = {
         polyOrder = basis:polyOrder(),
         basisType = basis:id()
      }
   }
   fld:clear(0.0)
   return fld
end

local function createProject(grid, basis)
   local projUp = Updater.EvalOnNodes {
      onGrid   = grid,
      basis    = basis,
      evaluate = function(t, xn) return 1 end,
      onGhosts = true,
   }
   return projUp
end


local fromIdx, toIdx = 1, 2

local fineGridIdx = fromIdx
if numCells[toIdx][1] > numCells[fromIdx][1] then fineGridIdx = toIdx end

for iT = 1, #tests do

   -- Grids and basis.
   local grid  = {createGrid(lower, upper, numCells[fromIdx], tests[iT]["periodicDirs"]),
                  createGrid(lower, upper, numCells[toIdx], tests[iT]["periodicDirs"])}
   local basis = createBasis(grid[fromIdx]:ndim(), pOrder, basisName)
   
   -- Fields.
   local phiDG  = {createField(grid[fromIdx],basis), createField(grid[toIdx],basis)}
   local phiFEM = {createField(grid[fromIdx],basis), createField(grid[toIdx],basis)}
   
   for i = 1,2 do
      fromIdx = i
      toIdx   = 3-i

      -- Project the test function onto the first grid.
      local project = createProject(grid[fromIdx], basis)
      project:setFunc(
         function (t, xn)
            local a  = tests[iT]["a"]
            local c  = tests[iT]["c"]
            local mu = tests[iT]["mu"]
            local periodicDirs = tests[iT]["periodicDirs"]
            return testFunction(xn, a, c, mu, periodicDirs)
         end)
      project:advance(0.0, {}, {phiDG[fromIdx]})
      phiDG[fromIdx]:write(string.format("phiDGin_%sP%i_Nx%i-Nx%i_%s.bp",basisName,pOrder,
                                         numCells[fromIdx][1],numCells[toIdx][1],tests[iT]["bcStr"]),0.0)
      
      -- Create the MG Poisson solver.
      local poissonSlv = Updater.MGpoisson {
         solverType = 'FEM',
         onGrid     = grid[fineGridIdx],
         basis      = basis,
         bcLower    = tests[iT]["bcLower"],
         bcUpper    = tests[iT]["bcUpper"],
      }
      
      -- Translate the DG field to an FEM field, and output the FEM field.
      poissonSlv:translateDGtoFEM(phiDG[fromIdx], phiFEM[fromIdx])
      phiFEM[fromIdx]:write(string.format("phiFEMin_%sP%i_Nx%i-Nx%i_%s.bp",basisName,pOrder,
                                          numCells[fromIdx][1],numCells[toIdx][1],tests[iT]["bcStr"]),0.0)
   
      -- Restrict/prolong the FEM field.
      if i==1 then
         poissonSlv:prolongFEM(phiFEM[fromIdx], phiFEM[toIdx])
      elseif i==2 then
         poissonSlv:restrictFEM(phiFEM[fromIdx], phiFEM[toIdx])
      end
   
      -- Output the data on the finer mesh.
      phiFEM[toIdx]:write(string.format("phiFEMout_%sP%i_Nx%i-Nx%i_%s.bp",basisName,pOrder,
                                        numCells[fromIdx][1],numCells[toIdx][1],tests[iT]["bcStr"]),0.0)
      
   end

end

