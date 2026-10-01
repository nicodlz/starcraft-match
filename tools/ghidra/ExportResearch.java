// @category StarCraft.Research
// Private export only. Function discovery and decompiler output are hypotheses.
import ghidra.app.script.GhidraScript;
import ghidra.framework.Application;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import com.google.gson.GsonBuilder;
import java.nio.file.*;
import java.nio.charset.StandardCharsets;
import java.util.*;

public class ExportResearch extends GhidraScript {
    private Path output;
    private String digest;
    private String addr(Address a) { return "0x" + a.toString().toUpperCase(); }
    private Map<String,Object> map(Object... xs) {
        Map<String,Object> m = new LinkedHashMap<>();
        for (int i=0; i<xs.length; i+=2) m.put((String)xs[i], xs[i+1]);
        return m;
    }
    private void save(String name, Object value) throws Exception {
        Files.write(output.resolve(name), (new GsonBuilder().serializeNulls().setPrettyPrinting()
            .create().toJson(value)+"\n").getBytes(StandardCharsets.UTF_8));
    }
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 2) throw new IllegalArgumentException("output directory and SHA-256 required");
        output = Paths.get(args[0]); digest = args[1];
        if (!digest.equalsIgnoreCase(currentProgram.getExecutableSHA256()))
            throw new IllegalArgumentException("Imported executable hash mismatch");
        Files.createDirectories(output);
        DecompInterface decompiler = new DecompInterface();
        if (!decompiler.openProgram(currentProgram)) throw new IllegalStateException("Decompiler failed");
        List<Object> functions = new ArrayList<>(), symbols = new ArrayList<>(), strings = new ArrayList<>();
        try {
            FunctionIterator fi = currentProgram.getFunctionManager().getFunctions(true);
            while (fi.hasNext()) {
                monitor.checkCancelled();
                Function f = fi.next();
                List<Object> instructions = new ArrayList<>(), calls = new ArrayList<>(), references = new ArrayList<>(), ranges = new ArrayList<>(), stringRefs = new ArrayList<>();
                AddressRangeIterator ri = f.getBody().getAddressRanges();
                while (ri.hasNext()) {
                    AddressRange r = ri.next();
                    ranges.add(map("start", addr(r.getMinAddress()), "end_inclusive", addr(r.getMaxAddress())));
                }
                InstructionIterator ii = currentProgram.getListing().getInstructions(f.getBody(), true);
                while (ii.hasNext()) {
                    Instruction ins = ii.next();
                    instructions.add(map("address", addr(ins.getAddress()), "text", ins.toString(), "length", ins.getLength()));
                    for (Reference ref : ins.getReferencesFrom()) {
                        if (ref.getReferenceType().isCall()) calls.add(map("from", addr(ref.getFromAddress()), "to", addr(ref.getToAddress())));
                        Data d = currentProgram.getListing().getDataAt(ref.getToAddress());
                        if (d != null && d.hasStringValue()) stringRefs.add(addr(d.getAddress()));
                    }
                }
                ReferenceIterator refs = currentProgram.getReferenceManager().getReferencesTo(f.getEntryPoint());
                while (refs.hasNext()) {
                    Reference ref = refs.next();
                    references.add(map("from", addr(ref.getFromAddress()), "type", ref.getReferenceType().toString()));
                }
                DecompileResults result = decompiler.decompileFunction(f, 30, monitor);
                String dc = result.decompileCompleted() && result.getDecompiledFunction()!=null ? result.getDecompiledFunction().getC() : null;
                Map<String,Object> record = map("schema_version", 1, "address", addr(f.getEntryPoint()),
                    "size", f.getBody().getNumAddresses(), "name", null, "proposed_names", Collections.singletonList(f.getName()),
                    "confidence", 0.5, "references", references, "calls", calls, "strings", stringRefs,
                    "status", "unknown", "boundary_verified", false, "body_ranges", ranges,
                    "calling_convention", f.getCallingConventionName(), "prototype", f.getSignature().toString(),
                    "binary_sha256", digest, "provenance", "Ghidra auto-analysis; manual review required",
                    "original_asm", instructions, "decompiler_output", dc, "decompiler_error", result.getErrorMessage());
                functions.add(record);
            }
            SymbolIterator si = currentProgram.getSymbolTable().getAllSymbols(true);
            while (si.hasNext()) {
                Symbol s = si.next();
                symbols.add(map("address", addr(s.getAddress()), "name", s.getName(), "source", s.getSource().toString()));
            }
            DataIterator di = currentProgram.getListing().getDefinedData(true);
            while (di.hasNext()) {
                Data d = di.next();
                if (d.hasStringValue()) {
                    List<Object> refsToString = new ArrayList<>();
                    ReferenceIterator r = currentProgram.getReferenceManager().getReferencesTo(d.getAddress());
                    while (r.hasNext()) refsToString.add(addr(r.next().getFromAddress()));
                    strings.add(map("address", addr(d.getAddress()), "text", String.valueOf(d.getValue()), "references", refsToString));
                }
            }
            save("functions.json", functions); save("symbols.json", symbols); save("strings.json", strings);
            save("manifest.json", map("schema_version", 1, "binary_sha256", digest, "ghidra_version", Application.getApplicationVersion(),
                "language", currentProgram.getLanguageID().toString(), "compiler_spec", currentProgram.getCompilerSpec().getCompilerSpecID().toString()));
        } finally { decompiler.dispose(); }
    }
}
